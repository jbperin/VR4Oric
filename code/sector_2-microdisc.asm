;
; This part of the code is a bit tricky: Basically the Atmos with Microdisc and the Telestrat despite using a similar boot 
; loading system are actually loading the boot sector at different addresses.
;
; Since the 6502 is not particularly well equiped to handle code that can be loaded at any address we had to find a trick.
; What we are doing is to make the code run at a particular address, and have a small module that makes sure that it is
; moved at the correct place wherever it was loaded in first place. That makes the code a lot easier to write :)
;
; Warning: This whole code CANNOT be more than 256 bytes (ie: the size of the sector)
;
; The bootloader will be placed in the screen area because we know that this is not going to be used by the operating system.
; By chosing an address in HIRES area, we also guarantee that it will not be visible on the screen (the Oric boots in TEXT).
;
#define FINAL_ADRESS	$9800			; First 256 bytes of the STD charset are invisible


#define OPCODE_RTS				$60

#define FDC_command_register	$0310
#define FDC_status_register		$0310
#define FDC_track_register		$0311
#define FDC_sector_register		$0312
#define FDC_data				$0313
#define FDC_flags				$0314
#define FDC_drq                 $0318	

#define FDC_Flag_DiscSide       %00010000

#define CMD_ReadSector			$80
#define CMD_Seek				$1F

#define wait_status_floppy 30

#include "floppy_description.h"       ; This file is generated by the floppy builder

	.zero
	
	*=$00
	
retry_counter		.dsb 1	; Number of attempts at loading data (ie: not quite clear what happens when this fails...)
	

	.text

	;
	; These are the 23 header bytes that goes before the actual executable part of the bootsector
	;
	.byt $00,$00,$FF,$00,$D0,$9F,$D0,$9F,$02,$B9,$01,$00,$FF,$00,$00,$B9,$E4,$B9,$00,$00,$E6,$12,$00

	.text

	;
	; Here starts the actual executable part, maximum available size is 233 bytes (256-23)
	;

	;
	; Try to find the load address
	;
	sei               	; Disable interruptions

	lda #OPCODE_RTS
	sta $00          	; Write in $00 Page => take one less byte
	jsr $0000     		; JSR on the RTS immediately return.

	;
	; Compute the absolute address of where the code we want to copy begins,
	; and save it in zero page ($00 and $01)
	;	
_start_relocator_
	tsx               	; Get stack offset
	dex
	clc
	lda $0100,x     	; Get LOW adress byte
	adc #<(_end_relocator_-_start_relocator_+1)
	sta $00
	lda $0101,x     	; Get HIGH adress byte
	adc #>(_end_relocator_-_start_relocator_+1)
	sta $01

	; Now $00 and $01 contain the adress of LABEL
	; We can now copy the whole code to it's new
	; location
	ldy #0
copy_loop
	lda ($00),y  
	sta FINAL_ADRESS,y
	iny
	cpy #(_END_-_BEGIN_)
	bne copy_loop
	
	jmp FINAL_ADRESS
_end_relocator_


;
; Here is some code compiled at a fixed adress in memory.
;

     *=FINAL_ADRESS

_BEGIN_
	;
	; Switch to HIRES
	;
	ldy #39 			; From $9900 to $c000 is 39 pages (9984 bytes)
	lda #0
loop_hires_outer	
	tax
loop_hires_inner
__auto_hires
	sta $9900,x
	inx
	bne loop_hires_inner
	inc __auto_hires+2
	dey
	bne loop_hires_outer

	lda #30				; Write hires switch
	sta $bfdf


	;
	; Read sector data
	; 
	ldy #4
	sty retry_counter
read_sectors_loop

readretryloop
	nop
	nop
	nop
	
read_one_sector
	;
	; Check if we are on the correct track already and if not
	; then send a SEEK command to the FDC to move the head to
	; the correct track.
	;
	ldx #FLOPPY_LOADER_TRACK
	cpx FDC_track_register
	beq track_ok
	
	; Write the track number in the FDC data register
	stx FDC_data

wait_drive2
	lda FDC_drq 				; We are waiting for the drive maybe not useful if drive is ready after the eprom boot
	bmi wait_drive2
	
	;
	; Send a SEEK command (change track)
	;
	lda #CMD_Seek
	sta FDC_command_register
	; 
	; Command words should only be loaded in the Command Register when the Busy status bit is off (Status bit 0). The one exception is the Force Interrupt command. 
	; Whenever a command is being executed, the Busy status bit is set. 
	; When a command is completed, an interrupt is generated and the busy status bit is reset. 
	; The Status Register indicates whethter the completed command encountered an error or was fault free. For ease of discussion, commands are divided into four types (I, II, III, IV).
	ldy #4
r_wait_completion
	dey
	bne r_wait_completion
r2_wait_completion
	lda FDC_status_register
	lsr
	bcs r2_wait_completion
	asl

track_ok	

	; Write the sector number in the FDC sector register
__auto__sector_index
	lda #FLOPPY_LOADER_SECTOR
	sta FDC_sector_register ;
	
	lda #%10000100 			; Force the system to use the Side 0 of the A: drive
	sta FDC_flags
			
	;
	; Send a READSECTOR command
	;
	lda #CMD_ReadSector
	sta FDC_command_register

	ldy #wait_status_floppy
waitcommand
	nop 					; Not useful but for old Floppy drive maybe
	nop 					; Not useful but for old Floppy drive maybe
	dey	
	bne waitcommand

	;
	; Read the sector data
	;
	ldy #0
fetch_bytes_from_FDC
	lda FDC_drq
	bmi fetch_bytes_from_FDC
	lda FDC_data
__auto_write_address
	sta FLOPPY_LOADER_ADDRESS,y

	iny
	bne fetch_bytes_from_FDC
	; Done loading the sector
	
	lda FDC_status_register
	and #$1C
		
	beq sector_OK
	dec retry_counter
	bne readretryloop
	
sector_OK
	inc __auto__sector_index+1
	inc __auto_write_address+2
	dec sector_counter
	bne read_sectors_loop

	;
	; Data successfully loader (we hope)
	;
	sei
	lda #%10000001 			; Disable the FDC (Eprom select + FDC Interrupt request)
	sta FDC_flags
	
	ldx #0                      ; 0 = Microdisc initialisation code
	jmp FLOPPY_LOADER_ADDRESS


sector_counter		.byt (($FFFF-FLOPPY_LOADER_ADDRESS)+1)/256


_END_

