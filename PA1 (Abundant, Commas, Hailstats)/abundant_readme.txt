CSCI 103 Abundant Commas Programming Assignment 

Name: Aidan McAlaine 

Email Address: amcalain@usc.edu

NOTE: You can delete the questions, we only need your responses.

NOTE: It is helpful if you write at most 80 characters per line,
and avoid including special characters, so we can read your responses.

Please summarize the help you found useful for this assignment, which
may include office hours, discussion with peers, tutors, et cetera.
Saying "a CP on Tuesday" is ok if you don't remember their name.
If none, say "none".

:

================================ Questions ==================================

1. Which kind of a loop did you use to iterate through the input numbers? 
   Why?
   
   I used a while loop because we aren't sure how many integers the user is going to input
   that are separated by white space. 

2. Which kind of a loop did you use to find the proper divisors for a
   single input number? Why?
   
   I used a for loop that began at 1 (the lowest divisor) and ended just before the number itself. 
   I did this because we know that we are only going to iterate up to the last number before the user-inputed number. 
   
3. Review the programming idioms linked on the website.  Identify 3 idioms
   you either used or could have used in this program and briefly explain
   where and how they were/could be used.

   1. The divisibility/factor idiom: I used this inside my for loop. If the integer was divisible by the number (i) being iterated, then it could be added to the sum of divisors. 
   2. The moving window (shifting values) idiom was used while adjusting values of n(1,2,3) and a(1,2,3)
   3. The lookup table idiom was used when determining if the present userInput value would fall into one of the top 3 abundant values. 
   
================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

:1 hour 

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

: N/A

Do you have any other remarks?

: N/A
