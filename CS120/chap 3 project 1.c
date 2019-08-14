#include stdio.h

int checkDates(int, int, int);

int main(void)
{
	int day;
	int month;
	int year;
	printf("Please enter the date in mm/dd/yyyy format.\n");
	scanf("%d/%d/%d" &month, &day, &year);
	if (checkDates(month, day, year))
	{
		printf("You entered the date %i%i%i" &year &month &day);
	}
}