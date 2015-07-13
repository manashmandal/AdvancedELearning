#ifndef QBOOLALGEBRA_H
#define QBOOLALGEBRA_H
#include <math.h>
#include <QString>
#include <QMap>
#include <QList>

typedef QMap <QString, QString> QVariableMap;

/***************** ALGORITHM ******************
 * ********************************************
 * ============================================
 * Developed by : Manash
 * LICENSE : MIT
 * C++ Qt Variant Class
 * ================= Here we go ===============
 * ********************************************
 *
 * ================= TRUTH TABLE MAKER & VERIFIER========
 * ******************************************************
 * ------------------ (I) PARSE THE INPUT ---------------
 * 1. Take the input string = in
 *
 * 2. Trim it in.trimmed();
 *
 * 3. Make every letter to uppercase
 *
 * 4. Replace A' / B' ... etc with lowercase letter like A' = a, B' = b [Using :  ]
 *
 * 5. Get the output from the function
 *
 * ------------------ First parsing ends here-------------
 *      #       #       #       #       #       #
 *  #       #       #       #       #       #       #
 * **************************************************************
 * -------------=---- (II) GENERATE INPUT VALUE -=-=-=-=-=-==-=-
 *
 * 1. How many variables are actually in that expression? To find out
 * ---- (a) Make a copy and lower each letter you come across
 *
 * ---- (b) Make an QString array (i.e variables), run a loop through that lowered expression, if (!variables.contains(loweredInput.at(i)) variables.prepend(loweredInput.at(i)) // Why 'prepend'? we'll get to that point later
 *
 * ---- (c) Now count the size of variables and put it in another variable, (i.e varSize = variables.size())
 *
 * ***********
 *
 * 2. Now we need to generate a verification table, to create it follow these steps
 * ----(a) let's say we have these variables in that array, variables = "cba" // Since we prepended it
 * The number of input combination can be calculated by this formula, 2^(Number of variables), for this example this will be 2^3 = 8 combinations, for the sake of simplicity, let's put it in a variable, combinations = pow(2, variables.size())
 *
 * ----(b) Now we will create a function that takes a size and repeatation number as arguments and returns a string, let's name it generateValue(size_t size, size_t repeatation)
 *
 * ----(c) What will be the body of function? It will have two nested loops, the main loop will contain other two loops (we can do better but let's stick with that for now)
 *
 * QString generateValue(size_t size, size_t repeatation){
 *      QString output;
 *      for (int i = 0; i < ((size) / pow(2, repeatation)); i++){
 *             for (int j  = 0; j < repeatation; j++) output.append("0");
 *             for (int k = 0; k < repeatation; k++) output.append("1");
 *       }
 *      return output;
 * }
 *
 * ----(d) Make sure you've reserved a QMap pointer, so we can dynamically manage memory for the number of variables. Now simply add the variables with their corresponding values by calling the function, map.insert(variables.at(i), generateValue(size, repeatation));
 *
 * Formula for repeatation is, rep = pow(2, index);
 *
 * It was needed to be prepended because of convention, since the repeatation formula is pow(2, index), so we needed to put the last one at the beginning of an array to get the index = 0, 1, 2 respectively, otherwise we'd get 0101.... for 'a' and 00001111... for 'c'. Now that's being resolved by putting 'c' at the beginning to get index 0.
 *
 * ----(e) Now we have both variables and their corresponding values. Next, we will parse the expression again in CPU readable form, let's do that.
 *
 * ********************************************************************
 *  -----(III) PARSE THE EXPRESSION AND PERFORM CALCULATION-----------
 * ********************************************************************
 *  I think this is my biggest challange, to transform the equation in an cpu readable form so that we can perform calculation easily. I'll use an stack algorithm to parse that.
 *
 *  1. First of all '*' should be placed in the modified expression to find out where the AND operation is happening. Let's create a function called, operatorAdder, which takes a QString for an argument and also returns a modified QString. We'll also add a left first bracket '(' at the beginning and a right first bracket ')' at the end to execute the algorithm. To do that:
 *
 * ---- (a)
 *  QString out = input;
 *
 *  for (int i = 0; i + 1 < out.size(); i++){
       if ((out[i].isLetter() && out[i+1].isLetter()) {out.insert(i+1, '*');}
   }
   out.insert(0, '(');
   out.insert(out.size(), ')');
 *  return out;
 *
 * 2. First phase is complete, now for the hard part. We need to process the modified and 'parenthesized' string and perform boolean operations based on the value to verify truth table
 *
 * --- (a) Create a stack, we will put a lot of things in it while we process the input string
 *
 * Let's take this expression for an example: (A*B+(C+D)E)
 *
 * and our stack: | - | -  | -  |  - | -  |
 *
 * // Since we trimmed the string and put required '*'s and '(' and ')' we don't need to worry about the input
 *
 * ---------(i)
 *
 *
 *
 * *******************************************************************/

class QBoolAlgebra
{
private:
    QVariableMap *map;
    size_t variable_number;


public:
    QBoolAlgebra();
    ~QBoolAlgebra();

    QString generateValues(size_t size, int repeatation);
};

#endif // QBOOLALGEBRA_H
