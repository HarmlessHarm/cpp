## Assignment 1 CPP
##### Author:
Harm Manders, 10677186

#### Instructions
`make run` creates executable `run.o` which runs code for assignment1   
`make testCode` creates executable `testCode.o` to run tests provided by assignment  
`make test` creates executable `test.o` to run test that checks random day of week generator
`make` runs all make commands

#### Comments
The test.o file generates a fraction that is pretty close to the expected value of 0.1423 which is equal to 1/7. You'd expect this value because approximately you'd guess 1 in 7 days correctly.

#### References
Inspiration to calculate days passed since 1900:
http://www.cplusplus.com/reference/ctime/mktime/   
Documentation non struct tm:
http://www.cplusplus.com/reference/ctime/tm/