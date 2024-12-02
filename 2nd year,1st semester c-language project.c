#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h> // Used for Sleep(ms) and Beep

// Function Prototypes
void Black(), Red(), Green(), Yellow(), Blue(), Purple(), Cyan(), White(), Reset();
void AlarmClock();
void calendar();
int getFirstDayOfTheYear(int year);
int february(int year);
void SpecificWeekDay(int date, int month, int year);

// Color Functions
void Black() { printf("\033[0;30m"); }
void Red() { printf("\033[0;31m"); }
void Green() { printf("\033[0;32m"); }
void Yellow() { printf("\033[0;33m"); }
void Blue() { printf("\033[0;34m"); }
void Purple() { printf("\033[0;35m"); }
void Cyan() { printf("\033[0;36m"); }
void White() { printf("\033[0;37m"); }
void Reset() { printf("\033[0m"); }

int main() {
    int c;
    while (1) {
        Green();
        printf("Option:\n");
        Reset();
        Blue();
        printf("1.Calendar\n");
        printf("2.Alarm Clock\n");
        printf("3.Exit\n");
        Reset();
        Yellow();
        printf("Enter Choice No: ");
        scanf("%d", &c);
        Reset();

        if (c == 1) {
            calendar();
        } else if (c == 2) {
            AlarmClock();
        } else if (c == 3) {
            break;
        } else {
            Red();
            printf("\nPlease Enter Correct Choice!!\n\n");
            Reset();
        }
    }
    printf("\n");
    Red();
    printf("              Program is Finished        \n");
    printf("                  Thank You!!            \n");
    Reset();
    return 0;
}

// Alarm Clock
void AlarmClock() {
    int hour, min, sec; // for system time
    int h, m, s;        // for user input

    // Get the current time from system clock
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    hour = t->tm_hour;
    min = t->tm_min;
    sec = t->tm_sec;

    Cyan();
    printf("%70s\n", "Enter Alarm Time (24 Hour Format)");
    Reset();
    Purple();
    printf("HOUR : ");
    scanf("%d", &h);
    printf("MINUTE : ");
    scanf("%d", &m);
    printf("SECOND : ");
    scanf("%d", &s);
    Reset();

    if (h > 24 || m > 60 || s > 60) {
        Red();
        printf("\t\tInvalid Time\n");
        printf("\t\tTry Again!!\n\n");
        Reset();
        return;
    }

    while (1) {
        system("cls"); // Clear screen
        printf("Alarm Time   = %02d:%02d:%02d\n", h, m, s);
        printf("Current Time = %02d:%02d:%02d\n", hour, min, sec + 1);
        Sleep(1000); // Wait 1 second
        sec++;
        if (sec == 60) { sec = 0; min++; }
        if (min == 60) { min = 0; hour++; }
        if (hour == 24) { hour = 0; }

        if (hour == h && min == m && sec == s) {
            for (int beep = 0; beep < 5; beep++) {
                Beep(750, 800);
            }
            Green();
            printf("Alarm Triggered! Time to Wake Up!\n");
            Reset();
            Purple();
            printf("Sending SMS: 'Your Alarm at %02d:%02d:%02d has Triggered!'\n", h, m, s);
            Reset();
            break;
        }
    }
}

// Calendar Function
void calendar() {
    char* months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int year, option;

    printf("\nEnter Year: ");
    scanf("%d", &year);

    if (year < 1583) {
        Red();
        printf("Please Enter a Year Above 1582\n");
        Reset();
        return;
    }

    daysInMonth[1] = february(year);

    printf("Options:\n");
    printf("1. View Full Year\n");
    printf("2. View Specific Month\n");
    printf("3. Exit\n");
    printf("Enter Choice: ");
    scanf("%d", &option);

    if (option == 3) return;

    for (int i = 0; i < (option == 1 ? 12 : 1); i++) {
        if (option == 2) {
            printf("Enter Month (1-12): ");
            int month;
            scanf("%d", &month);
            if (month < 1 || month > 12) {
                Red();
                printf("Invalid Month!\n");
                Reset();
                return;
            }
            i = month - 1;
        }

        printf("\n\n%20s %d\n", months[i], year);
        printf("Sun Mon Tue Wed Thu Fri Sat\n");

        int weekDay = getFirstDayOfTheYear(year);
        for (int j = 0; j < weekDay; j++) printf("    ");

        for (int day = 1; day <= daysInMonth[i]; day++) {
            if (weekDay == 0) Red(); // Sunday
            else Reset();
            printf("%3d ", day);
            weekDay++;
            if (weekDay > 6) {
                weekDay = 0;
                printf("\n");
            }
        }
        printf("\n");
        Reset();
    }
}

// Helper Functions
int getFirstDayOfTheYear(int year) {
    return (year * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
}

int february(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
}

