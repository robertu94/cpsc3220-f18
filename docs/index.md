# Introduction to Operating Systems 

CPSC/ECE 3220 -- Section 002 -- Fall 2018

## Course Metadata

Time and Location: MW 14:30-15:45 (Jordan Hall G033)

Instructor: Robert Underwood, <robertu@.clemson.edu>

Office: 221 McAdams

Office Hours: TBD

By appointment as needed

## Course Materials

The course materials described below are living documents and will be updated as the semester progresses.
Students are expected to review these documents regularly (i.e. at least once a week)

Course Website: [robertu94.github.io/cpsc3220-f18](robertu94.github.io/cpsc3220-f18)

Schedule:  [Google Calendar](https://calendar.google.com/calendar/embed?src=g.clemson.edu_q3ufj6c56eevjftssug8tfnpeg%40group.calendar.google.com&ctz=America%2FNew_York)

Repository: [git clone https://github.com/robertu94/cspc3220-f18](https://github.com/robertu94/cspc3220-f18)

Assignment Submissions: [handin.cs.clemson.edu](handin.cs.clemson.edu)

The class will also make use of [Canvas](clemson.instructure.edu) for grading, on-line quizzes, and course discussion.
Questions that could be helpful to all students should be asked on canvas.
This allows me to answer questions once rather than many times.
You should **NOT** post project source code or specific implementation information.
Such behavior may be considered a violation of academic integrity.

All project requirements are posted in the course repository.
The repository is managed using Git.
If you are unfamiliar with Git, I recommend the [Atlassian tutorial](https://www.atlassian.com/git/tutorials/learn-git-with-bitbucket-cloud) or the [Git Book](https://git-scm.com/book/en/v2) if you need a more complete reference.
Learning a source control management tool such as git well now will pay huge dividends once you get into industry.
I can't express how important it is to learn this skill sooner rather than later.

### Recommended Texts

There is no required textbook for this course.
Sufficient material will be presented in class to complete all assignments.
However, there are numerous free on-line sources that I have found useful in my study of operating system:

+	[Three Easy Pieces](http://pages.cs.wisc.edu/~remzi/OSTEP/#book-chapters) -- An introductory operating system textbook that is free online
+	[The Linux Kernel](https://github.com/torvalds/linux) -- the source code for the Linux kernel
+	[Linux Cross Reference](https://elixir.bootlin.com/linux/v4.16.9/source) -- a on-line quick-reference for Linux
+	[The FreeBSD Kernel and Base System](https://github.com/freebsd/freebsd) -- the source code for the FreeBSD kernel


## Course Goals

The goal of this class is to prepare you to use both **fundamental** and **emerging** topics in operating systems **design** and **development** to equip you to **solve** and **analyze** computing problems.

+	By **fundamental**, I mean classical disciplines of operating systems such as but not limited to OS interfaces and facilities (system calls, interupts, pseudo file systems), time sharing (processes, threads, scheduling, synchronization, interprocess communication), virtual memory (allocation, paging), mass storage (filesystems, hardware, swapping), hardware interfaces.
+	By **emerging**, I mean more recent developments in operating systems design such as resilience, and more advanced security features.
+	By **design** I mean the processes of selecting or creating appropriate abstractions to represent system resources.
+	By **development** I mean actual understanding implementation concerns when implementing designs and their performance impacts.
+	By **solve** I mean that you will implement and use operating system features in user space to solve real programming problems.
+	By **analyze** I mean that you will consider the design of a system and be able to make informed decisions of the performance and security impacts of a design

### Learning Outcomes

By the end of the course students will be able to:

+	Explain the **fundamental** and **emerging** concepts in Operating Systems described above
+	Explain the interactions between hardware and software that are expressed in modern operating system
+	Be able to analyze trade-offs in system designs related to the above concepts
+	Implement system monitoring tools that use OS facilities such as ptrace to observe operating system behavior
+	Implement a threading library and a selection of synchronization primitives
+	Implement policies for dynamic memory allocation.

This is not a course on how to program.  Proficient programming ability in either C or C++ is expected, and you will likely get better at programming when you finish.

## Prerequisites

+	CPSC 2120 and CPSC 2310 with a C or better; or ECE 2230 and ECE 2720 with a C or better.
+	Proficient with either C or C++
+	Comfortable in a UNIX/Linux command line environment

## Grading

Weighting

+	Assignments 50%
+	Quizes 10%
+	Midterm 15%
+	Final 20%
+	Participation 5%

Grading Scale 

+	A: $90 \leq x 100$
+	B: $80 \leq x < 90$
+	C: $70 \leq x < 80$
+	D: $60 \leq x < 70$
+	F: $60 < x$

I reserve the right to adjust the grading scale and/or weightings if necessary in the favor of students.

## Readings

I may assign readings from time to time.  The content of readings may used in quizzes or exams at my discretion.

## Assignments

There will be several programming assignments (probably 4).
All assignments will be graded on a School of Computing lab machine.
These must be submitted by 17:00 Eastern Standard Time to the handin.cs.clemson.edu server.
Late submissions will not be accepted under any circumstances.
In the event a late submission, your last non-late submission will be used if available.
Failure to submit an assignment by the deadline will result in a 0 on the assignment.

To encourage early submissions I will utilize an Autograder that will allow you to test your submissions against my test cases daily prior to the deadline.
Because assignments are machine graded and there will be multiple opportunities to submit to the Autograder for each assignment, no deviations from the program specification will be tolerated.
I recommend starting early, testing extensively on your own, and submitting often to achieve a positive outcome.

The autograder will provide feedback each day that you upload a new submission by noon.
The feedback will provide information on which test cases you passed or failed.
It takes time to grade all assignments even for an autograder -- especially as the deadline approaches.
In the event you don't get a response by 1pm:  You should try the following, in order: 1) check your SPAM folder. 2) make sure that you really did submit new code. 3) make sure that the code you submitted wasn't the same as your previous submissions (the autograder only grades new code). 4) contact the grader. 5) contact me.

## Quizes

I will give short "pop quizzes" at the beginning of every class that will be used in part to take attendance.
These quizzes may require you to enter information distributed during classes to ensure that you attend in person.
If you miss a quiz, your grade will be a zero.
I will drop the lowest 3 quizzes.

## Exams

There will be a midterm and final exam.  The content of these exams are cumulative and comprehensive.  The time and date are in the schedule.

## Office Hours

Office hours are an opportunity to reinforce course topics 1 on 1 or in small groups.  If you have a university approved reason (I.E. Class, illness, family emergency, or other university approved activity) that you can't attend office hours, I am happy to make an appointment.
You are required to attend office hours at least once prior the midterm exam; failure to do so will result in a participation score of 0.


## Participation

You are expected to participate in class activities (ask questions, make comments, contribute to activities).
Doing so is for your good.
I will assign participation points coarsely: 100% to fully-engaged students, 50% to nominally engaged (physically attend, but not volunteering questions/comments), and 0% for students who don't show up or are trying to hide.

Attendance is critical in this class.
Not only is the material highly cumulative, hints and examples for projects will be given for projects.
Any student with more then 3 unexcused absences will be dropped from the course.

Being absent, excused or not, does not change the responsibility for assigned work or material covered during the class. Excused absences require documentation. For University-sponsored events, students must provide written notice prior to the event. For all other excused absences, students should provide written documentation to the instructor as soon as possible.

As a rule, No make up quizzes or exam will be given.
If you arrive late, you will not be given additional time to complete the quiz or test.

If I should ever be more than 10 minutes late, you may assume that class has been canceled.
In this case, please check email for further explanation.

## Laptop Policy

You are expected to have a laptop with a Linux programming environment running the Linux kernel (natively or in a VM).
There will also be electronic quizzes that you will be expected to complete during class.
You may also want to follow along with the programming examples presented during lecture.

I also expect the following, both as a courtesy to your classmates, to yourself, and to me:

+	Laptop speakers and alarms should be set to mute or off before coming to class.
+	All Facebook, email, IM, etc MUST be turned off during class. If you engage in unauthorized communication or entertainment during class (e.g. surfing the web, instant messaging, playing games, etc.), you will be asked to leave. Repeat offenders will be dropped from the class. If this activity occurs during an exam or quiz, it constitutes academic dishonesty (see following).
+	Cell phones and pagers are to be turned OFF and will not be used under any circumstance during the class period.
+	The use of earphones for anything, such as an iPod, is prohibited during class.

## Labs

There is no lab section for this course; however, the Ubuntu lab machines (joeys, adas, or koalas) will be used to test all of your assignments. Before submitting any code, you should make sure that it compiles and runs correctly on these machines. If your program doesn't work on the lab machines, then it doesn't work.

## Grading Appeals

I do occasionally make mistakes. If you think I made a mistake when grading an assignment, quiz, or exam, you should email me, with detailed justification, within one week of the date the grades are available. If you don't, your original grade will stand.

## Email Policy

Email is the most effective way to contact me with individual issues (please use Canvas for general issues).
I check email frequently between 8am and 5pm weekdays and will generally respond within 24 hours.
As a rule, I will not respond to email after 5pm or before 8am.

Remember that failure to plan and prepare on your part, does not constitute a crisis on mine. If you send me a project-related email right before a deadline, I may not answer it in time to be helpful.

## Students with Disabilities

In accordance with the University’s policy, I will do my best to provide reasonable accommodations to students with disabilities. Students should contact Student Disability Services and myself to discuss their individual needs for accommodation as early as possible—at least a week before special accommodations are needed. 

## Getting Help

If you need help during this course, talk to me sooner rather than later; often a brief discussion will clarify things enough to get you back on track. The longer you wait, the harder it will be to catch up.

If you are consistently having problems with the course content, you can also seek help from the Academic Success Center and take advantage of the tutoring and supplemental instruction opportunities they offer on a regular basis. If your specific class is not listed, the ASC will begin sessions for groups of three or more. The tutoring schedule is [available online](http://www.clemson.edu/asc/tutoring/index.html).

## Academic Integrity

Attempts to cheat on any graded activity will not be tolerated.

The following represent a non-exhaustive list of academic integrity violations:

+	If I suspect that you attempted to cheat the Autograder in any way such as by performing a denial of service attack, attempting to invalidly modify the autograder's any score produced by the autograder, or extract confidential information from the autograder: you will receive a score of zero, and this will be treated an academic integrity violation.
+	If I suspect that you submitted work that is not your own, you will receive a score of 0, and this will be treated as an academic integrity violation.
+	If I suspect that you performed unauthorized communication or utilize unauthorized resources during an exam or quiz, you will receive a score of 0, and this will be treated as an academic integrity violation.
+	If I suspect that you attempt to falsify class roll for yourself or others in any way, you will receive a 0 on all graded activities that day, and this will be treated as an academic integrity violation.

As members of the Clemson University community, we have inherited Thomas Green Clemson's vision of this institution as a “high seminary of learning.” Fundamental to this vision is a mutual commitment to truthfulness, honor, and responsibility, without which we cannot earn the trust and respect of others. Furthermore, we recognize that academic dishonesty detracts from the value of a Clemson degree. Therefore, we shall not tolerate lying, cheating, or stealing in any form.

Following the Clemson University Code of Student Conduct, academic dishonesty of any kind will be reported to the Clemson University Academic Integrity Committee. In the event that the committee reaches a finding of guilt, the student(s) involved in the misconduct will receive an automatic F for the semester. I will also recommend, at the board’s discretion, that the participating students be dismissed from the university. I take this policy very seriously. The University’s statement on academic integrity is posted here. The Clemson School of Computing Academic Honesty Policy can be found here.

## Title IX

The Clemson University Title IX (Sexual Harassment) statement must be included: Clemson University is committed to a policy of equal opportunity for all persons and does not discriminate on the basis of race, color, religion, sex, sexual orientation, gender, pregnancy, national origin, age, disability, veteran's status, genetic information or protected activity in employment, educational programs and activities, admissions and financial aid. This includes a prohibition against sexual harassment and sexual violence as mandated by Title IX of the Education Amendments of 1972. This policy is located at http://www.clemson.edu/campus- life/campus-services/access/title-ix/. Ms. Alesia Smith is the Clemson University Title IX Coordinator, and the Executive Director of Equity Compliance. Her office is located at 110 Holtzendorff Hall, 864.656.3181 (voice) or 864.656.0899 (TDD)

### Acknowledgments

I would like to thank my various operating systems and systems instructors who formed my understandings of these topics and inspired the structure for this class.
Special thanks to Dr. Jacob Sorber, who designed several of the course projects and from whom I borrowed the structure of this document.

+	[Dr. Jacob Sorber](https://people.cs.clemson.edu/~jsorber/courses/cpsc3220-S18/)
+	[Dr. Robert Geist](https://people.cs.clemson.edu/~geist/public_html/822/syl_822_short.pdf)
+	[Dr. Rong Ge](https://people.cs.clemson.edu/~rge/cpsc8240/syllabus.html)
+	[Dr. Mark Smotherman](https://people.cs.clemson.edu/~mark/3220.html)

