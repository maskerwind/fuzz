# Minimized Crash Input
*  
    i 00NNNNNNNONNNNNNNNNNNNNNNNN0
    
    i 0ZZZZZZZZZZZZZZZZZZZZZZZZZ00
    
    i 00KKKKKKKKKKKKKKKKKKKKKKKKK0
    
    i 00kkkkkkkkkkkkkkkkkkkkkkkkk0
    
    i 0hhhhhhhhhhhhhhhhhhhhhhhht
    
    
    i 00EEEEEEEEEEEEEEEEEEEEEEEEE0
    
    i 00CCCCCCCCCCCCCCGCCCCCCCCCC0
    
    i 0a
    i 8a
    e 0a0
    
    i 0a
    i 7a
    e 0a0
    
    e 0aKKKKKKKKKKKKKKKKKKKKKKKK
    
    
    i 0a
    i 5a
    e 0a0
    
    i 0a
    i 0b
    e 0a0
    
    i 2a
    i 0a
    e 2a0
    
    i 0OOOOOOOOOOOOOOOOOOOOOOOOO00
    
    i 00UUUUUUUUUUUUUUUUUUUUUUUUU0
    
    e 00ajjjjjjjjjjqjjjjjjjjjjjjj0
    
    i 0a
    i 2a
    e 0a0
    
    e 0aaEEEEEEEEEEEEEEEEEEEEEEE
    
    
    i 0b
    i 0a
    e 0b000000
    
    i 0a
    i 1a
    e 0a0
    
    i 0a
    i 5a
    e 0a0
    
    i 0mmmmmmmmmmmmmmmmmmmmmmmmm00
    
    i 0HHHHHHHHHHHHHHHHHHHHHHHHH
    
    
    c 0SSSSSSSSSSSSSSSSSSSSSSSSS
    
    
    c 0TTTTTTTTTTTTTTTTTTTTTTTTT
    
    
    i 00bXXXXXXXXXBXXXXXXXXXXXXXb0
    
    i 00KKKKKKKKKKKKKKKKKKKKKKKKK0
    
    i 00FFFFFFFFFFFFFFFFFFFFFFFFF0
    
    i 00sssssssssssssssssssssssss0
    
    i 00MoMMoMMMMMMMMMMMMMMMMMMMM0
    
    i 00IIIIIIIIIIIIIIIIIIIIIIIII0
    
    i 0BBBBBBBBBBBBBBBBBBBBBBBFB00
    
    c0 0kkkkkkkkkkkkkkkkkkkkkkkkk0
    
    i 00JJJJJJJJJJJJJJJJJJJJJJJJJ0
    
    i 00ddddddddddddddddddddddddd0
    
    i 0CCCCCCCCCCCCCCCCCCCCCCCCa
    
    
    i 0rrrrrrrrrrrrrrrrrrrrrrrrr00
    
    i 0wwwwwwwwwwwwwwwwwwwwwwwwp
    
    
    e 00caaaaaaaaaaaaaaaaaaaaaaaa0
    
    i 0a
    i 8a
    e 0a0
    
    i 0a
    i 0b
    e 0a0
    
    i 0a
    i 2a
    e 0a0
    
    i 0a
    i 3a
    e 0a0
    
    i 00sUUUUUUUUUUUUUUUUUUUUUUUU0
    
    i 0Ecccccccccccccccccccccccc00
    
    c 0aOOOOOOOOOOOOOOOOOOOOOOOO00
* It seems that all the crash input can be categorized as two types, one of which is the overflow of characters while the other one involves erase function. We can now reproduce the crashes and check what is going on.
 
# Log from gdb
* Test example: i 00NNNNNNNONNNNNNNNNNNNNNNNN0
	* gdb output: 

		(gdb) r
		The program being debugged has been started already.
		Start it from the beginning? (y or n) y
		Starting program: /home/masker/fuzzing/assignment/software-security-assignment-groups-27/sint 

		> i 00NNNNNNNONNNNNNNNNNNNNNNNN0
		Invalid input

		> x

		Bye.
		*** stack smashing detected ***: /home/masker/fuzzing/assignment/software-security-assignment-groups-27/sint terminated

		Program received signal SIGABRT, Aborted.
		0x00007ffff7a42428 in __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:54
		54	../sysdeps/unix/sysv/linux/raise.c: no such file or dictory.
		(gdb)

* Test example: 
		i 0a
		i 8a
		e 0a0
	* gdb output:

		(gdb) r
		The program being debugged has been started already.
		Start it from the beginning? (y or n) y
		Starting program: /home/masker/fuzzing/assignment/software-security-assignment-groups-27/sint 
		
		> i 0a
		
		> i 8a
		
		> e 0a0
		
		Program received signal SIGSEGV, Segmentation fault.
		sortedcontainer_erase (sc=sc@entry=0x60c010, data=0x60c910) at sortedcontainer.c:147
		147	           else  parent->right =  child_ptr;
		(gdb)
	* Fix
		When the node to be deleted is the root, an error appears because the following code is wrong at first. It should be fixed like this
 
			if (head == NULL) -> if (parent == NULL)


