#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    char doctor[50];
};

/* Add patient */
void addPatient() {
    struct Patient p;
    FILE *fp = fopen("patients.dat", "ab");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("\nEnter Patient ID: ");
    scanf("%d", &p.id);
    getchar();

    printf("Enter Name: ");
    fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();

    printf("Enter Disease: ");
    fgets(p.disease, 50, stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    printf("Enter Doctor Name: ");
    fgets(p.doctor, 50, stdin);
    p.doctor[strcspn(p.doctor, "\n")] = 0;

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("\nPatient added successfully!\n");
}

/* View all patients */
void viewPatients() {
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Patient Records ---\n");

    while (fread(&p, sizeof(p), 1, fp)) {
        printf("\nID: %d", p.id);
        printf("\nName: %s", p.name);
        printf("\nAge: %d", p.age);
        printf("\nDisease: %s", p.disease);
        printf("\nDoctor: %s\n", p.doctor);
    }

    fclose(fp);
}

/* Search patient */
void searchPatient() {
    struct Patient p;
    int id, found = 0;
    FILE *fp = fopen("patients.dat", "rb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Patient ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("\nRecord Found!");
            printf("\nName: %s", p.name);
            printf("\nAge: %d", p.age);
            printf("\nDisease: %s", p.disease);
            printf("\nDoctor: %s\n", p.doctor);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nPatient not found!\n");
}

/* Delete patient */
void deletePatient() {
    struct Patient p;
    int id, found = 0;
    FILE *fp = fopen("patients.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Patient ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id != id)
            fwrite(&p, sizeof(p), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    if (found)
        printf("\nPatient deleted successfully!\n");
    else
        printf("\nPatient not found!\n");
}

int main() {
    int choice;

    do {
        printf("\n===== Patient Record Management =====\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: printf("\nExiting...\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
