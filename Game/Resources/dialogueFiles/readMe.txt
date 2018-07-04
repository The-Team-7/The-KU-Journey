Important to know: Each file represents a conversation 

#1: begin dialogue with name of person speaking
	options:
		<Karun>
		<Bijay>
		<Prabhat>
		<Anup>
	note:
		the order can be anything
		dont use excessive spaces use only if needed. 


#2: previous person's dialogue should be closed before new Person starts to speak
	options:
		<ed>
	example:
		<Anup>
		........
		.......
		<ed>
		<Bijay>
		

#3: you can add a repeating dialogue to a file as:
		<repeatingDialogue>
	note: it will be said by whoever said the last line. or can be set with a dummy line
		<Prabhat>
		<ed>
		<repeatingDialogue>
		this is repeating dialogue


#4: you can add <br> for line change. 
	note:Dont add it more than once.
