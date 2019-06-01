#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	struct checkin{
		char name[20];
		int age;
		int id;
	};

	printf("Insert your name, age and ID\n");
	
	struct checkin person;
	
	scanf("%s",person.name);
	scanf("%d",&person.age);
	scanf("%d",&person.id);
	getchar();

	printf("You are all set\n");


	return 0;
}
