#=================================================================
# Copyright 2021 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================

# P1-2
# Student Name: Rahul Mone
# Date: 3/5/2021
#
# This program solves a match puzzle.

.data
Reference:   .alloc 1				# allocate space for reference pattern
Candidates:  .alloc 8				# allocate space for puzzle candidates

.text
MPuzzle:	addi	$1, $0, Reference	# set memory base
		
		add		$30, $0, $31
		addi	$7, $0, 5
		swi	582			# create and display puzzle

		lw		$1, 0($1)			#load packed values of reference into $1
		addi	$3, $0, 28
Loadcan:		addi	$28, $0, 3
		addi	$6, $0, 32
		addi	$2, $3, Candidates  #load memory address of candidates into $2
		
		lw		$2, 0($2)			#load memory address of first candidate into register2

		
Compare:	addi	$6, $6, -4
		beq		$7, $0, Flip		# go to flip if the rotate has occured 4 times
		and		$4, $1, $28
		and		$5, $2, $28
		sll		$28, $28, 2

		beq		$0, $6, End			#jump to end if matches
		beq		$4, $5, Compare		#jump to next thing to compare if matches
		beq		$3, $0, Rotate		#if cycled through all candidates, rotate

		addi	$3, $3, -4
		bne		$4, $5, Loadcan		#load a new candidate if the squares dont match



End:	swi	583			# highlight and report match
		jr      $31			# return to operating system

#------------------------------------------------------------------

Rotate:	andi	$26, $1, 61440		#rotate the square 
		andi	$1, $1, 4095
		sll		$1, $1, 4
		srl		$26, $26, 12
		or		$1, $1, $26
		addi	$3, $0, 28
		addi	$7, $7, -1

		j		Loadcan

Flip:	addi	$1, $0, Reference	#function to flip the square
		lw		$1, 0($1)

		addi	$2, $0, 0
		andi	$5, $1, 3
		sll		$5, $5, 4
		add		$2, $2, $5

		andi	$5, $1, 12
		add		$2, $2, $5

		andi	$5, $1, 48
		srl		$5, $5, 4
		add		$2, $2, $5

		andi	$5, $1, 49152
		srl		$5, $5, 8
		add		$2, $2, $5

		andi	$5, $1, 12288
		srl		$5, $5, 4
		add		$2, $2, $5

		andi	$5, $1, 3072
		add		$2, $2, $5

		andi	$5, $1, 768
		sll		$5, $5, 4
		add		$2, $2, $5

		andi	$5, $1, 192
		sll		$5, $5, 8
		add		$2, $2, $5

		add		$1, $0, $2
		addi	$7, $0, 10
		addi	$3, $0, 28

		j		Loadcan





