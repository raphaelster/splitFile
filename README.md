# splitFile
Small C++ program to split an input file along a regex delimiter, and save to files with a name equal to a regex capture group.

Usage:
splitFile [FILE] [REGEX_CAPTURE] [REGEX_FILENAME (uses capture group 1)] [EXTENSION]

Ex:
given file1.txt:
	"It turns out, this is a
	
	 surprisingly annoying problem to solve with
	 pure Bash, so
	 
	 I wrote this C++ program
	 
	 It works pretty well, I think"
	 
the command:
	splitFile file1.txt '\n\n' '([A-Z][A-Za-z]*)' asdf
	
will split file1.txt into:
	"It turns out, this is a"
	"surprisingly annoying problem to solve with
	 pure Bash, so"
	"I wrote this C++ program"
	"It works pretty well, I think"
	
and save the results to:
	"It turns out, this is a" > It.asdf
	"surprisingly annoying problem to solve with
	 pure Bash, so" > Bash.asdf
	"I wrote this C++ program" > I.asdf
	"It works pretty well, I think" > It.asdf
	
	
Some considerations:
	Will overwrite files without asking
	Uses the first capture group for the filename, and reports an error if the filename can't be found

	 

	 
		
	