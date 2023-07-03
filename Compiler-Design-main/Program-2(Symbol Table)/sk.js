// To execute:
// If you have a lex code and you want to give a text file to it to generate tokens from the code inside that file and 
// generate tokens in the output.txt file 
// do this 
// ./a.out <input.txt> output.txt

// Using let, var, and const

// Variable declaration using let
let x = 5;
let y = 10;

// Variable declaration using var
var z = 15;

// Constant declaration using const
const PI = 3.14159;

// If statement
if (x < y) {
    console.log("x is less than y");
} else {
    console.log("x is greater than or equal to y");
}

// While loop
let i = 0;
while (i < 5) {
    console.log(i);
    i++;
}

// For loop
for (let j = 0; j < 5; j++) {
    console.log(j);
}

// Array declaration and manipulation
let myArray = [1, 2, 3, 4, 5];
console.log(myArray[2]); // Output: 3
myArray.push(6); // Add an element to the end of the array
console.log(myArray); // Output: [1, 2, 3, 4, 5, 6]

// Function declaration
function multiply(a, b) {
    return a * b;
}

let result = multiply(3, 4);
console.log(result); // Output: 12

// Switch statement
let day = 1;
switch (day) {
    case 1:
        console.log("Monday");
        break;
    case 2:
        console.log("Tuesday");
        break;
    default:
        console.log("Other day");
}
