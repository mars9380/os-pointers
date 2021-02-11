// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <cmath>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;

    student.f_name = new char[128];
    student.l_name = new char[128];

    student.id = promptInt("Please enter the student's id number: ", 0, 999999999);
    std::cin.ignore();

    std::cout << "Please enter the student's first name: ";
    std::cin.getline(student.f_name, 128);

    std::cout << "Please enter the student's last name: ";
    std::cin.getline(student.l_name, 128);

    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217727);
    std::cout << std::endl;
    std::cin.ignore();

    student.grades = new double[student.n_assignments];

    for(int i = 0; i < student.n_assignments; i++){
        std::string msg = "Please enter grade for assignment " + std::to_string(i) + ": ";
        student.grades[i] = promptDouble(msg, 0, 1000);
    }
    std::cout << std::endl;

    calculateStudentAverage(&student, &average);

    average = std::round(average * 10.0) / 10.0;

    printf("Student: %s %s [%d]\n  Average grade: %.1f\n", student.f_name, student.l_name, student.id, average);

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    // Code to prompt user for an int

    std::string input;
    int value;

    bool isValidNumber = false;

    while (isValidNumber != true){
        isValidNumber = true;
        std::cout << message;
        std::cin >> input;

        if (input.length() > 9){
            isValidNumber = false;
        }
        for(int i = 0; i < input.length(); i++){
            if (isdigit(input[i]) == false){
                isValidNumber = false;
            }    
        }
        if (isValidNumber == false){
            std::cout << "Sorry, I cannot understand your answer\n";
        } else if (isValidNumber == true){
            if (std::stoi(input) < min || std::stoi(input) > max){
                isValidNumber = false;
                std::cout << "Sorry, I cannot understand your answer\n";
            }
        }     
    }
    value = std::stoi(input);

    return value;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    // Code to prompt user for a double

    double value;
    std::string input;
    std::size_t pos;

    bool success = false;

    while (success == false){
        std::cout << message;
        std::cin >> input;
        try {
            value = std::stod(input, &pos);
            if (pos < input.size()){
                success = false;
                std::cout << "Sorry, I cannot understand your answer\n";
            } else {
                if (value < min || value > max){
                    success = false;
                    std::cout << "Sorry, I cannot understand your answer\n";
                } else {
                    success = true;
                }
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Sorry, I cannot understand your answer\n";
        } catch (const std::out_of_range&) {
            std::cout << "Sorry, I cannot understand your answer\n";
        }
    }
    return value;
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade

    Student *student = (Student*)object;

    double total = 0;

    for(int i = 0; i < student->n_assignments; i++){
        total += student->grades[i];
    }

    *avg = total/student->n_assignments;
}
