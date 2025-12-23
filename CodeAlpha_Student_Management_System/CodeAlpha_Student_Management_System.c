#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

void addStudent(FILE *file) {
    struct Student student;
    printf("Enter ID: ");
    scanf("%d", &student.id);
    printf("Enter Name: ");
    scanf("%s", student.name);
    printf("Enter Age: ");
    scanf("%d", &student.age);
    printf("Enter Marks: ");
    scanf("%f", &student.marks);

    fseek(file, 0, SEEK_END);
    fwrite(&student, sizeof(struct Student), 1, file);
    printf("Student added.\n");
}

void displayStudents(FILE *file) {
    struct Student student;
    rewind(file);  // Go to the beginning of the file
    printf("ID\tName\tAge\tMarks\n");
    while(fread(&student, sizeof(struct Student), 1, file)) {
        printf("%d\t%s\t%d\t%.2f\n", student.id, student.name, student.age, student.marks);
    }
}

void searchStudent(FILE *file) {
    int id;
    struct Student student;
    int found = 0;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    rewind(file);
    while(fread(&student, sizeof(struct Student), 1, file)) {
        if(student.id == id) {
            printf("ID: %d\nName: %s\nAge: %d\nMarks: %.2f\n", student.id, student.name, student.age, student.marks);
            found = 1;
            break;
        }
    }
    if(!found) {
        printf("Student not found.\n");
    }
}

void updateStudent(FILE *file) {
    int id;
    struct Student student;
    int found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    FILE *tempFile = fopen("temp.dat", "wb");
    if(tempFile == NULL) {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(file);
    while(fread(&student, sizeof(struct Student), 1, file)) {
        if(student.id == id) {
            printf("Enter new Name: ");
            scanf("%s", student.name);
            printf("Enter new Age: ");
            scanf("%d", &student.age);
            printf("Enter new Marks: ");
            scanf("%f", &student.marks);
            found = 1;
        }
        fwrite(&student, sizeof(struct Student), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found) {
        printf("Student updated.\n");
    } else {
        printf("Student not found.\n");
    }
}

void deleteStudent(FILE *file) {
    int id;
    struct Student student;
    int found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    FILE *tempFile = fopen("temp.dat", "wb");
    if(tempFile == NULL) {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(file);
    while(fread(&student, sizeof(struct Student), 1, file)) {
        if(student.id != id) {
            fwrite(&student, sizeof(struct Student), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found) {
        printf("Student deleted.\n");
    } else {
        printf("Student not found.\n");
    }
}

int main() {
    FILE *file = fopen("students.dat", "rb+");
    if(file == NULL) {
        file = fopen("students.dat", "wb+");
        if(file == NULL) {
            printf("Error opening file.\n");
            return 1;
        }
    }

    int choice;
    while(1) {
        printf("\n1. Add Student\n2. Display Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            addStudent(file);
        } else if(choice == 2) {
            displayStudents(file);
        } else if(choice == 3) {
            searchStudent(file);
        } else if(choice == 4) {
            updateStudent(file);
        } else if(choice == 5) {
            deleteStudent(file);
        } else if(choice == 6) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    fclose(file);
    return 0;
}