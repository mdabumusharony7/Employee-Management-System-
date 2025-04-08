#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char jobTitle[50];
    char department[30];
    float salary;
};

void displayHeading() {
    printf("\n=====================================\n");
    printf("   EMPLOYEE MANAGEMENT SYSTEM\n");
    printf("=====================================\n");
}

int authenticateUser() {
    char username[50], password[50], storedUsername[50], storedPassword[50];
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("⚠ Error opening users file for reading!\n");
        return 0;
    }

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    while (fscanf(file, "%s %s", storedUsername, storedPassword) != EOF) {
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}


void addEmployee() {
    FILE *file = fopen("employees.txt", "a");
    if (!file) {
        printf("⚠ Error opening file for writing!\n");
        return;
    }

    struct Employee emp;
    
    printf("Enter Employee ID: ");
    if (scanf("%d", &emp.id) != 1) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        return;
    }
    printf("Enter Name: ");
    if (scanf(" %49[^\n]", emp.name) != 1) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        return;
    }
    printf("Enter Job Title: ");
    if (scanf(" %49[^\n]", emp.jobTitle) != 1) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        return;
    }
    printf("Enter Department: ");
    if (scanf(" %29[^\n]", emp.department) != 1) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        return;
    }
    printf("Enter Salary: ");
    if (scanf("%f", &emp.salary) != 1 || emp.salary < 0) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        return;
    }

    fprintf(file, "%d,%s,%s,%s,%.2f\n", emp.id, emp.name, emp.jobTitle, emp.department, emp.salary);
    fclose(file);
    
    printf("✅ Employee added successfully!\n");
}


void viewEmployees() {
    FILE *file = fopen("employees.txt", "r");
    if (!file) {
        printf("⚠ Error opening file for reading!\n");
        return;
    }

    struct Employee emp;
    
    printf("\n===== Employee List =====\n");
    while (fscanf(file, "%d,%49[^,],%49[^,],%29[^,],%f\n", &emp.id, emp.name, emp.jobTitle, emp.department, &emp.salary) != EOF) {
        printf("ID: %d | Name: %s | Job: %s | Department: %s | Salary: %.2f\n", emp.id, emp.name, emp.jobTitle, emp.department, emp.salary);
    }
    fclose(file);
}


void markAttendance() {
    FILE *file = fopen("attendance.txt", "a");
    if (!file) {
        printf("⚠ Error opening file for writing!\n");
        return;
    }

    int id;
    char status[10];

    printf("Enter Employee ID: ");
    if (scanf("%d", &id) != 1) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        return;
    }
    printf("Enter Status (Present/Absent): ");
    if (scanf("%9s", status) != 1) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        return;
    }

    fprintf(file, "%d,%s\n", id, status);
    fclose(file);

    printf("✅ Attendance recorded successfully!\n");
}


void viewAttendance() {
    FILE *file = fopen("attendance.txt", "r");
    if (!file) {
        printf("⚠ Error opening file for reading!\n");
        return;
    }

    int id;
    char status[10];

    printf("\n===== Attendance Records =====\n");
    while (fscanf(file, "%d,%9s\n", &id, status) != EOF) {
        printf("ID: %d | Status: %s\n", id, status);
    }
    fclose(file);
}


void managePayroll() {
    FILE *file = fopen("payroll.txt", "a");
    if (!file) {
        printf("⚠ Error opening file for writing!\n");
        return;
    }

    int id;
    float salary;

    printf("Enter Employee ID: ");
    if (scanf("%d", &id) != 1) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        return;
    }
    printf("Enter Salary Amount: ");
    if (scanf("%f", &salary) != 1 || salary < 0) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        return;
    }

    fprintf(file, "%d,%.2f\n", id, salary);
    fclose(file);

    printf("✅ Payroll updated successfully!\n");
}


void searchEmployee() {
    FILE *file = fopen("employees.txt", "r");
    if (!file) {
        printf("⚠ Error opening file for reading!\n");
        return;
    }

    struct Employee emp;
    int id, found = 0;

    printf("Enter Employee ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d,%49[^,],%49[^,],%29[^,],%f\n", &emp.id, emp.name, emp.jobTitle, emp.department, &emp.salary) != EOF) {
        if (emp.id == id) {
            printf("\n===== Employee Details =====\n");
            printf("ID: %d\nName: %s\nJob: %s\nDepartment: %s\nSalary: %.2f\n", emp.id, emp.name, emp.jobTitle, emp.department, emp.salary);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("⚠ Employee not found!\n");
    }

    fclose(file);
}


void removeEmployee() {
    FILE *file = fopen("employees.txt", "r");
    if (!file) {
        printf("⚠ Error opening file for reading!\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("⚠ Error opening temporary file for writing!\n");
        fclose(file);
        return;
    }

    struct Employee emp;
    int id, found = 0;

    printf("Enter Employee ID to remove: ");
    if (scanf("%d", &id) != 1) {
        printf("⚠ Invalid input!\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    while (fscanf(file, "%d,%49[^,],%49[^,],%29[^,],%f\n", &emp.id, emp.name, emp.jobTitle, emp.department, &emp.salary) != EOF) {
        if (emp.id != id) {
            fprintf(tempFile, "%d,%s,%s,%s,%.2f\n", emp.id, emp.name, emp.jobTitle, emp.department, emp.salary);
        } else {
            found = 1;
            printf("Employee with ID %d found and will be removed.\n", id); 
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        if (remove("employees.txt") == 0) {
            printf("Old employees.txt file removed successfully.\n"); 
        } else {
            printf("Error removing old employees.txt file.\n"); 
        }
        if (rename("temp.txt", "employees.txt") == 0) {
            printf("Temporary file renamed to employees.txt successfully.\n"); 
        } else {
            printf("Error renaming temporary file to employees.txt.\n"); 
        }
        printf("✅ Employee removed successfully!\n");
    } else {
        remove("temp.txt");
        printf("⚠ Employee not found!\n");
    }
}


void chatbot() {
    char input[100];
    printf("\n===== Chatbot =====\n");
    printf("Hello! I am your assistant. How can I help you today?\n");
    printf("You can ask me about:\n");
    printf("1. Adding an employee\n");
    printf("2. Viewing employees\n");
    printf("3. Marking attendance\n");
    printf("4. Viewing attendance\n");
    printf("5. Managing payroll\n");
    printf("6. Searching for an employee\n");
    printf("7. Removing an employee\n");
    printf("Type 'exit' to leave the chatbot.\n");

    while (1) {
        printf("\nYou: ");
        scanf(" %[^\n]", input);

        if (strcmp(input, "exit") == 0) {
            printf("Chatbot: Goodbye!\n");
            break;
        } else if (strstr(input, "add employee") != NULL) {
            printf("Chatbot: To add an employee, go to the main menu and select 'Add Employee'. You will need to provide the employee's ID, name, job title, department, and salary.\n");
        } else if (strstr(input, "view employees") != NULL) {
            printf("Chatbot: To view all employees, go to the main menu and select 'View Employees'. This will display a list of all employees with their details.\n");
        } else if (strstr(input, "mark attendance") != NULL) {
            printf("Chatbot: To mark attendance, go to the main menu and select 'Mark Attendance'. You will need to provide the employee's ID and their attendance status (Present/Absent).\n");
        } else if (strstr(input, "view attendance") != NULL) {
            printf("Chatbot: To view attendance records, go to the main menu and select 'View Attendance'. This will display a list of all attendance records.\n");
        } else if (strstr(input, "manage payroll") != NULL) {
            printf("Chatbot: To manage payroll, go to the main menu and select 'Manage Payroll'. You will need to provide the employee's ID and the salary amount.\n");
        } else if (strstr(input, "search employee") != NULL) {
            printf("Chatbot: To search for an employee, go to the main menu and select 'Search Employee'. You will need to provide the employee's ID to find their details.\n");
        } else if (strstr(input, "remove employee") != NULL) {
            printf("Chatbot: To remove an employee, go to the main menu and select 'Remove Employee'. You will need to provide the employee's ID to remove them from the system.\n");
        } else {
            printf("Chatbot: I'm sorry, I didn't understand that. Please ask about adding, viewing, marking attendance, viewing attendance, managing payroll, searching, or removing an employee.\n");
        }
    }
}


void menu() {
    int choice;
    do {
        printf("\n===== Main Menu =====\n");
        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Mark Attendance\n");
        printf("4. View Attendance\n");
        printf("5. Manage Payroll\n");
        printf("6. Search Employee\n");
        printf("7. Remove Employee\n");
        printf("8. Chatbot\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: markAttendance(); break;
            case 4: viewAttendance(); break;
            case 5: managePayroll(); break;
            case 6: searchEmployee(); break;
            case 7: removeEmployee(); break;
            case 8: chatbot(); break;
            case 9: printf("🔴 Exiting...\n"); break;
            default: printf("⚠ Invalid choice, try again.\n");
        }
    } while (choice != 9);
}


int main() {
    displayHeading();
    if (authenticateUser()) {
        printf("✅ Authentication successful!\n");
        menu();
    } else {
        printf("❌ Authentication failed! Exiting...\n");
    }
    return 0;
}
