# tower-of-hanoi
Tower of Hanoi (Advanced Version)


C program which solves for an extended and generalised version of the classic ‘Tower Of Hanoi’ problem.

Shows step-by-step transformation of any valid initial arrangement of ‘Tower of Hanoi’ blocks 
  to any desired valid desired arrangement of the same blocks.


Input is to be provided in 'main()' method of 'HANOI.C' 



Input consists of two 3D-arrays of 'int' data-type, with names 'T1' for Initial-Configuration and 'T2' for Final-Configuration. 


Input Example with Explaination : 

T1 = { { {1,4} , {2,4} , {1,2} } ,  /*Tower-1 with following blocks starting from lower-most block :  [ A-4 , B-4 , A-1] */
       { {1, -1} } ,                /*Tower-2 is empty since weight of its first-block is '-1' */
       { {1, -1} } }                /*Tower-3 is empty since weight of its first-block is '-1' */

T2 = { { {1,2} } , 
       { {1,-1} } , 
       { {1,4} , {2,4} } }


'T1' from above represents the following     ||     'T2' from above represents the following 3 towers : 
    A-2                                      ||                                   
    B-4                                      ||                               B-4 
    A-4    <EMPTY>    <EMPTY>                ||         A-2    <EMPTY>        A-4 
Tower-1    Tower-2    Tower-3                ||     Tower-1    Tower-2    Tower-3 
    Initial-Arrangement                      ||  Final/Desired Arrangement (consists of the same blocks as Initial-Arrangement but in a different arrangement) 

The first element of T1 ie {1,4} corresponds to the lower-most block A-4 in Tower-1. Here 'A' is type of the block and '4' is block's weight.

/*  Base -----> Top    weight of first block = -1 for Empty Tower */
/* {type,weight} types : 1 = A , 2 = B , 3 = C , etc. weights start from 1 */
/* T1 = Initial Tower , T2 = Final Tower */
  
  
  Final/Desired arrangement 'T2' is a different arrangement of the exact same blocks present in 'T1' 
  There must not be any additional blocks in 'T2' 
  'T2' must not have any blocks missing when compared to 'T1' 
  
  'T2' merely differs in arrangement of the same blocks present in 'T1' 
  
Important - 
  As per the Rules of Tower-Of-Hanoi, 
    Any of the Towers in T1 or T2 must not contain a heavier block on top of a lighter block.
    This rule is obeyed during transformation of arrangement 'T1' to arrangement 'T2'
  
The program displays a step-by-step solution to Transforming arrangement 'T1' to arrangement 'T2' while obeying the rules of Tower-Of-Hanoi.


