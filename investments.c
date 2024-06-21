//Program to figure out if it is more beneficial to pay off your loans first before investing or if you should only make the minimum payments and invest the rest.

#include <stdio.h>
#include <math.h>

//declaring all functions
double getPositiveDoubleInput(const char *prompt);
int getPositiveIntegerInput(const char *prompt);
double getValidMonthly(const char *prompt, double monthlyPayment);
int getValidAge(const char *prompt, int currentAge);
double calculateMonthlyInterest(double annualRate);
double calculateSavings(double loans, double loanInterestRate, double minLoanPayment, double monthlyPayment, int currentAge, int retirementAge, double investmentRate);
double calculateSavingsnoLoans(double loans,double loanInterestRate, double monthlyPayment, int currentAge, int retirementAge, double investmentRate);

//Input validation for getting a positive double 
double getPositiveDoubleInput(const char *prompt) { // prints the prompt
    double value;
    printf("%s", prompt);
    scanf("%lf", &value);
    while (value < 0) {
        printf("%s", prompt);
        while (getchar() != '\n'); // Clear input buffer
        scanf("%lf", &value);
    }
    return value;
}

// Function to validate and get a positive integer input
int getPositiveIntegerInput(const char *prompt) { // prints the prompt
    int value;
    printf("%s", prompt);
    scanf("%d", &value);
    while (value < 0) {
        printf("%s", prompt);
        while (getchar() != '\n'); // Clear input buffer
        scanf("%d", &value);
    }
    return value;
}

//input validation for monthly payment amount
double getValidMonthly(const char *prompt, double minLoanPayment) { // prints the prompt, checks if the value is more than the minimum Loan payment
    double value;
    printf("%s", prompt);
    scanf("%lf", &value);
    while (value < minLoanPayment) {
        printf("%s", prompt);
        while (getchar() != '\n'); // Clear input buffer
        scanf("%lf", &value);
    }
    return value;
}

//Input validation for age
int getValidAge(const char *prompt, int currentAge){ // prints the prompt, checks if the retirement age is more than current ages
    int retirementAge;
    printf("%s", prompt);
    scanf("%d", &retirementAge);
    while (retirementAge < currentAge) {
        printf("%s", prompt);
        while (getchar() != '\n'); // Clear input buffer
        scanf("%d", &retirementAge);
    }
    return retirementAge;
}

//Function to calculate monthly interest
double calculateMonthlyInterest(double annualRate) { // takes in the annual rate (loan/investment) to give the monthly interest
    return annualRate / 12.0;
}

// Function to calculate total investment amount by grdually paying off the loan
double calculateSavings(double loans, double loanInterestRate, double minLoanPayment, double monthlyPayment, int currentAge, int retirementAge, double investmentRate) {
//takes in the user given values for loans, loan interest rate, minimum loan payment, monthly payment, age, retirement age, annual investment rate

    double monthlyLoanInterest = calculateMonthlyInterest(loanInterestRate);
    double monthlyInvestmentInterest = calculateMonthlyInterest(investmentRate);
    double savings = 0.00;
    

    for (int age = currentAge; age < retirementAge; ++age) {

        double remainingMoney = monthlyPayment - minLoanPayment; // Reset remaining Money at the start of each year
        
        for (int i = 0; i < 12; ++i) {
            
            if (loans == 0) {
                remainingMoney = monthlyPayment;
            } 
            else if (loans < minLoanPayment) {
                loans += (loans * monthlyLoanInterest);
                remainingMoney = monthlyPayment - loans;
                loans = 0;
            } 
            else {
                loans += (loans * monthlyLoanInterest);
                loans -= minLoanPayment;
            }

            savings += (savings * monthlyInvestmentInterest);
            savings += remainingMoney;
        }
    }
    
    savings -= loans; // Subtract remaining loans from total savings
    
    return savings; // returns savings
}

// Function to calculate total investment amount after paying the loan completely
double calculateSavingsnoLoans(double loans,double loanInterestRate, double monthlyPayment, int currentAge, int retirementAge, double investmentRate){
//takes in the user given values for loans, loan interest rate, minimum loan payment, monthly payment, age, retirement age, annual investment rate

    double monthlyLoanInterest = calculateMonthlyInterest(loanInterestRate);
    double savings = 0.00;
    double monthlyInvestmentInterest = calculateMonthlyInterest(investmentRate);
    double remainingMoney;

    for(int age = currentAge; age < retirementAge; ++age){
        
        for (int i = 0; i < 12; ++i) {
            
            if (loans == 0) {
                savings += (savings * monthlyInvestmentInterest);
                savings += monthlyPayment;
            } 
            else if (loans < monthlyPayment) {
                loans += (loans * monthlyLoanInterest);
                remainingMoney = monthlyPayment - loans;
                savings += remainingMoney;
                loans = 0;
            } 
            else {
                loans += (loans * monthlyLoanInterest);
                loans -= monthlyPayment;
            }

            
        }
    }

    if(savings < loans){
        savings -= loans;
    }
    
    return savings;//returns savings
}


int main() {
    double loans, loanInterestRate, minLoanPayment, monthlyPayment, investmentRate;
    int currentAge, retirementAge;

    // Get user input
    loans = getPositiveDoubleInput("Enter how much you owe in loans: ");

    loanInterestRate = getPositiveDoubleInput("Enter the annual interest rate of the loans: ");

    minLoanPayment = getPositiveDoubleInput("Enter your minimum monthly loan payment: ");

    monthlyPayment = getValidMonthly("Enter how much money you will be putting towards loans/retirement each month: ", minLoanPayment);

    currentAge = getPositiveIntegerInput("Enter your current age: ");

    retirementAge = getValidAge("Enter the age you plan to retire at: ", currentAge);

    investmentRate = getPositiveDoubleInput("Enter your predicted annual rate of return: ");

    // Calculate total savings if only minimum payments are made on loans

    double savingsWithLoans = calculateSavings(loans, loanInterestRate, minLoanPayment, monthlyPayment, currentAge, retirementAge, investmentRate);

    //Calculate total savings if loan payment is made at once and the rest is invested

    double savingsWithoutLoans = calculateSavingsnoLoans(loans, loanInterestRate, monthlyPayment, currentAge, retirementAge, investmentRate);


    if (savingsWithLoans >= savingsWithoutLoans) { // check which is a better option depending on user input
        printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n");
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you paid off your loan before investing.\n", savingsWithLoans, savingsWithoutLoans);
    } 
    else {
        printf("You should apply all $%.2lf towards your loan before making any investments.\n", monthlyPayment);
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you only made minimum payments.\n", savingsWithoutLoans, savingsWithLoans);
    }

    return 0;
}
