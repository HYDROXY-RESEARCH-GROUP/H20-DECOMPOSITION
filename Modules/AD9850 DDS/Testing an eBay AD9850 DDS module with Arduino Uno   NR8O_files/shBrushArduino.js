/**
 * SyntaxHighlighter
 * http://alexgorbatchev.com/SyntaxHighlighter
 *
 * SyntaxHighlighter is donationware. If you are using it, please donate.
 * http://alexgorbatchev.com/SyntaxHighlighter/donate.html
 *
 * @version
 * 3.0.83 (July 02 2010)
 * 
 * @copyright
 * Copyright (C) 2004-2010 Alex Gorbatchev.
 *
 * @license
 * Dual licensed under the MIT and GPL licenses.
 */
;(function()
{
	// Arduino Code Highlighter
	typeof(require) != 'undefined' ? SyntaxHighlighter = require('shCore').SyntaxHighlighter : null;

	function Brush()
	{
		// Custom Arduino Brush Copyright 2011  Elabz.com http://elabz.com/
		// Dual licensed under the MIT and GPL licenses.
	
		var datatypes =	'void boolean char unsigned char byte int unsigned int ' +
						'word long unsigned long float double string String array ';

		var keywords =	'HIGH LOW INPUT OUTPUT ' +
						'false true ';
		var ports 	 =	'PORTB PORTC PORTD ' +
						'DDRB DDRC DDRD PINB PINC PIND';
					
		var functions =	'setup loop ' + // Structure
						'sizeof ' + // Utilities
						'if else for switch case while do break continue return goto ' + // Control Structures
						'pinMode digitalWrite digitalRead ' + // Digital I/O
						'analogReference analogRead analogWrite ' + // Analog I/O					
						'tone noTone shiftOut shiftIn pulseIn ' + // Advanced I/O
						'millis micros delay delayMicroseconds ' + // Time						
						'min max abs constrain map pow sqrt ' + // Math						
						'sin cos tan ' + // Trigonometry						
						'randomSeed random ' + // Random Numbers						
						'lowByte highByte bitRead bitWrite bitSet bitClear bit ' + // Bits and Bytes
						'attachInterrupt detachInterrupt ' + // External Interrupts
						'interrupts noInterrupts ' + // Interrupts
						'serial'; // Communication

		this.regexList = [
			{ regex: SyntaxHighlighter.regexLib.singleLineCComments,	css: 'comments' },			// one line comments
			{ regex: SyntaxHighlighter.regexLib.multiLineCComments,		css: 'comments' },			// multiline comments
			{ regex: SyntaxHighlighter.regexLib.doubleQuotedString,		css: 'string' },			// strings
			{ regex: SyntaxHighlighter.regexLib.singleQuotedString,		css: 'string' },			// strings
			{ regex: /^ *#.*/gm,										css: 'preprocessor' },
			{ regex: new RegExp(this.getKeywords(ports), 'gm'),		css: 'color2 bold' },
			{ regex: new RegExp(this.getKeywords(datatypes), 'gm'),		css: 'color1' },
			{ regex: new RegExp(this.getKeywords(functions), 'gm'),		css: 'functions bold' },
			{ regex: new RegExp(this.getKeywords(keywords), 'gm'),		css: 'keyword bold' },	
			{ regex: /B[0-9]{8}/gm,										css: 'keyword' } // Binary Notation
			
			];
	};

	Brush.prototype	= new SyntaxHighlighter.Highlighter();
	Brush.aliases	= ['arduino', 'avr'];

	SyntaxHighlighter.brushes.Arduino = Brush;

	// CommonJS
	typeof(exports) != 'undefined' ? exports.Brush = Brush : null;
})();
