/*
 * Homework 2:
 * Text file processor, takes an input file of lines of grades delimited 
 * by commas, and formats the data cleanly and presents statistics about 
 * the data. 
 * 
 * Author: Chase Urban
 * Due: February 3rd, 2020
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

double getTotalGrade(int q1, int q2, int q3, int q4, int q5, int q6, 
        int t1, int t2, int fe);

char getLetterGrade(double totalGrade);

/**
 * Opens the input and output files, processes in the input file, and 
 * outputs it in a well formatted fashion to the output file along with 
 * statistics about the data itself.
 */
int main(int argc, char** argv) {
    ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");
    int id, q1, q2, q3, q4, q5, q6, t1, t2, fe;
    double totalGrade = 0, maxTotal = 0, avgTotal = 0, avgQuiz = 0, 
            avgExam = 0;
    char charCursor = ' ', grade = ' ';
    string ln, fn;
    int maxQuiz = 0, totalQuizzes = 0, maxExam = 0, totalExams = 0, 
            totalTotals = 0, aS = 0, bS = 0, cS = 0, dS = 0, eS = 0;
    
    //Prints the spreadsheet header
    output << left << setw(7) << "ID" << setw(10) << "L_Name" << setw(10)
         << "F_Name" << setw(4) << "Q1" << setw(4) << "Q2" << setw(4) 
         << "Q3" << setw(4) << "Q4" << setw(4) << "Q5" << setw(5) << "Q6"
         << setw(5) << "T1" << setw(5) << "T2" << setw(7) << "Final" 
         << setw(7) << "Total" << setw(6) << "Grade" << endl;
    
    //Processes while not eof
    do{                                             
        //Takes the id from input
        input >> id;                                    
        //charCursor is used to throw away commas
        input >> charCursor;            
        ln = "";
        //Reads the last name until a comma is seen
        while(input.peek() != ','){   
            input >> charCursor;
            ln = ln + charCursor;
        }
        input >> charCursor;
        fn = "";
        //Reads the first name until a comma is seen
        while(input.peek() != ','){  
            input >> charCursor;
            fn = fn + charCursor;
        }
        input >> charCursor;
        //Reads in the rest of the quiz and test grades
        input >> q1;              
        if(q1 > maxQuiz) maxQuiz = q1;
        avgQuiz += q1;
        input >> charCursor;
        input >> q2;
        if(q2 > maxQuiz) maxQuiz = q2;
        avgQuiz += q2;
        input >> charCursor;
        input >> q3;
        if(q3 > maxQuiz) maxQuiz = q3;
        avgQuiz += q3;
        input >> charCursor;
        input >> q4;
        if(q4 > maxQuiz) maxQuiz = q4;
        avgQuiz += q4;
        input >> charCursor;
        input >> q5;
        if(q5 > maxQuiz) maxQuiz = q5;
        avgQuiz += q5;
        input >> charCursor;
        input >> q6;
        if(q6 > maxQuiz) maxQuiz = q6;
        avgQuiz += q6;
        input >> charCursor;
        input >> t1;
        if(t1 > maxExam) maxExam = t1;
        avgExam += t1;
        input >> charCursor;
        input >> t2;
        if(t2 > maxExam) maxExam = t2;
        avgExam += t2;
        input >> charCursor;
        input >> fe;
        if(fe > maxExam) maxExam = fe;
        avgExam += fe;

        //Calculates the total grades inputted for averaging
        totalQuizzes += 6;   
        totalExams += 3;

        //Gets total grade
        totalGrade = getTotalGrade(q1, q2, q3, q4, q5, q6, t1, t2, fe);   

        //Gets letter grade from total grade
        grade = getLetterGrade(totalGrade);

        //Adds to letter counter for letter grade
        switch(grade){
            case 'A': aS++; break;
            case 'B': bS++; break;
            case 'C': cS++; break;
            case 'D': dS++; break;
            case 'E': eS++; break;
            default: break;
        }

        totalTotals++;

        if(totalGrade > maxTotal) maxTotal = totalGrade;
        avgTotal += totalGrade;

        //Prints individual grade lines to output file
        output << left << setw(7) << id << setw(10) << ln 
             << setw(10) << fn << right << setw(2) << q1 << setw(4) << q2 
             << setw(4) << q3 << setw(4) << q4 << setw(4) << q5 << setw(4) 
             << q6 << setw(5) << t1 << setw(5) << t2 << setw(8) << fe 
             << setw(7) << setprecision(4) << totalGrade << setw(3) 
             << right << grade << endl;

    }while(!input.eof());
    
    //Calculates the average of the grades for quizzes, tests, and totals
    avgQuiz = avgQuiz / totalQuizzes;
    avgExam = avgExam / totalExams;
    avgTotal = avgTotal / totalTotals;
    
    //Outputs statistics to output file
    output << endl << left << setw(30) << "The maximum of all quizzes:" 
           << right << setw(5) << maxQuiz << endl << left << setw(30) 
           << "The average of all quizzes:" << right << setw(5) 
           << setprecision(3) << avgQuiz << endl << left << setw(30) 
           << "The maximum of all exams:" << right << setw(5) 
           << setprecision(4) << maxExam << endl << left << setw(30) 
           << "The average of all exams:" << right << setw(5) << avgExam 
           << endl << left << setw(30) << "The maximum of the totals:" 
           << right << setw(5) << maxTotal << endl << left << setw(30) 
           << "The average of the totals:" << right << setw(5) << avgTotal
           << endl << left << setw(30) << "The total number of A's:" 
           << right << setw(5) << aS << endl << left << setw(30) 
           << "The total number of B's:" << right << setw(5) << bS << endl
           << left << setw(30) << "The total number of C's:" << right 
           << setw(5) << cS << endl << left << setw(30) 
           << "The total number of D's:" << right << setw(5) << dS << endl 
           << left << setw(30) << "The total number of E's:" << right 
           << setw(5) << eS << endl;
    
    
    //Closes input and output files   
    input.close();
    output.close();
    return 0;
}

/**
 * Takes all grades and calculates final weighted grade
 * Preconditon: quizzes must be between 0 and 10, 
 *              exams must be between 0 and 100
 * Postcondition: returns total percentage grade
 */
double getTotalGrade(int q1, int q2, int q3, int q4, int q5, int q6, 
        int t1, int t2, int fe){
    double totalGrade;
    //Drops lowest quiz grade
    if(q1 <= q2 && q1 <= q3 && q1 <= q4 && q1 <= q5 && q1 <= q6)
        totalGrade += (((q2 + q3 + q4 + q5 + q6)*2)*0.25);
    else if(q2 <= q3 && q2 <= q4 && q2 <= q5 && q2 <= q6)
        totalGrade += (((q1 + q3 + q4 + q5 + q6)*2)*0.25);
    else if(q3 <= q4 && q3 <= q5 && q3 <= q6)
        totalGrade += (((q1 + q2 + q4 + q5 + q6)*2)*0.25);
    else if(q4 <= q5 && q4 <= q6)
        totalGrade += (((q1 + q2 + q3 + q5 + q6)*2)*0.25);
    else if(q5 <= q6)
        totalGrade += (((q1 + q2 + q3 + q4 + q6)*2)*0.25);
    else
        totalGrade += (((q1 + q2 + q3 + q4 + q5)*2)*0.25);  
    totalGrade += (t1 * 0.25);
    totalGrade += (t2 * 0.25);
    totalGrade += (fe * 0.25);
    return totalGrade;
}

/**
 * Finds letter grade for total grade
 * Precondition: total grade between 0 and 100
 * Postcondition: char containing letter grade
 */
char getLetterGrade(double totalGrade){
    if (totalGrade > 90) return 'A';
    else if (totalGrade > 80) return 'B';    
    else if (totalGrade > 70) return 'C';    
    else if (totalGrade > 60) return 'D';    
    else return 'E';  
}