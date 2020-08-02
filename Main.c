#include "Countries.h"
#include "HashTable.h"

static status fileRead(const char *, hashTable, int);


/*************************************************************************************************
**************************************Main Function***********************************************
 *************************************************************************************************/
int main(int argc, char *argv[]) {

	char CountryName[300], CityName[300], FamiliarFood[300];

	int option = 1, numberOfCountries, hashNumber;
	int PopulationNumber, x1, y1, x2, y2;
	const char *path = argv[3];
	sscanf(argv[2], "%d", &numberOfCountries);
	sscanf(argv[1], "%d", &hashNumber);
	hashTable Atlas = createHashTable(copyCountryName,freeCountryName, prinCountryName,
			deepCopyOfCountryObject, freeAllocatedMemoryOfCountry,printCountry,
			isEqualCountry,transformCountryIntoNumberFunction, hashNumber);

	if (fileRead(path, Atlas, numberOfCountries) == failure) {
		printf("no memory available");
		destroyHashTable(Atlas);
		Atlas = NULL;
		return 1;
	}

	while (option != 8) {

		printf("please choose one of the following numbers:\n");
		printf("1 : print countries\n");
		printf("2 : add country\n");
		printf("3 : add city to country\n");
		printf("4 : delete city from country\n");
		printf("5 : print country by name\n");
		printf("6 : delete country\n");
		printf("7 : is country in area\n");
		printf("8 : exit\n");
		scanf("%d", &option);

		switch (option) {

		case 1:
			if (displayHashElements(Atlas) == failure) {
				printf("print failed");
				destroyHashTable(Atlas);
				return 1;
			}
			break;

		case 2:
			printf("please enter a new country name\n");
			scanf("%s", CountryName);
			if (lookupInHashTable(Atlas, CountryName) != NULL) {
				printf("country with this name already exist\n");
				break;
			}
			printf("please enter two x and y coordinates :x1,y1,x2,y2\n");
			scanf("%d,%d,%d,%d", &x1, &y1, &x2, &y2);
			Country newCountry = addCountry(CountryName, x1, y1, x2, y2);
			if (newCountry == NULL) {
				printf("no memory allocated\n");
				destroyHashTable(Atlas);
			}
			if (addToHashTable(Atlas, CountryName, newCountry) == failure) {
				printf("no memory allocated\n");
				freeAllocatedMemoryOfCountry(newCountry);
				newCountry =NULL;
				destroyHashTable(Atlas);
				return 1;
			}
			freeAllocatedMemoryOfCountry(newCountry);
			break;

		case 3:
			printf("please enter a country name\n");
			scanf("%s", CountryName);
			if (lookupInHashTable(Atlas, CountryName) == NULL) {
				printf("country not exist\n");
				break;
			}
			printf("please enter a city name\n");
			scanf("%s", CityName);
			if (searchCity(lookupInHashTable(Atlas, CountryName),CityName)==true) {
				printf("the city already exist in this country\n");
				break;
			}
			printf("please enter the city favorite food\n");
			scanf("%s", FamiliarFood);
			printf("please enter number of residents in city\n");
			scanf("%d", &PopulationNumber);
			if (addCity(lookupInHashTable(Atlas, CountryName),CityName,FamiliarFood,PopulationNumber)==failure) {
				printf("no memory available\n");
				destroyHashTable(Atlas);
				return 1;
			}
			break;

		case 4:
			printf("please enter a country name\n");
			scanf("%s", CountryName);
			if (lookupInHashTable(Atlas, CountryName) == NULL) {
				printf("country name not exist.\n");
				break;
			}
			printf("please enter a city name\n");
			scanf("%s", CityName);
			if (searchCity(lookupInHashTable(Atlas, CountryName),CityName)==false) {
				printf("the city not exist in this country\n");
				break;
			}
			if (removeCity(lookupInHashTable(Atlas, CountryName),CityName)==failure){
				destroyHashTable(Atlas);
				return 1;
			}
			break;

		case 5:
			printf("please enter a country name\n");
			scanf("%s", CountryName);
			if (lookupInHashTable(Atlas, CountryName) == NULL) {
				printf("country name not exist\n");
				break;
			}
			if (printCountry(lookupInHashTable(Atlas, CountryName))==failure){
				destroyHashTable(Atlas);
				return 1;
			}
			break;

		case 6:
			printf("please enter a country name\n");
			scanf("%s", CountryName);
			if (lookupInHashTable(Atlas, CountryName) == NULL) {
				printf("can't delete the country\n");
				break;
			}
			if(removeFromHashTable(Atlas,CountryName)==failure){
				printf("there was a problem with the delete\n");
				destroyHashTable(Atlas);
				return 1;
			}
			printf("country deleted\n");
			break;

		case 7:
			printf("please enter a country name\n");
			scanf("%s", CountryName);
			if (lookupInHashTable(Atlas, CountryName) == NULL) {
				printf("country name not exist\n");
				break;
			}
			printf("please enter x and y coordinates:x,y\n");
			scanf("%d,%d", &x1, &y1);
			if(isCoordinateInCountry(lookupInHashTable(Atlas, CountryName),x1,y1)==false){
				printf("the coordinate not in the country\n");
				break;
			}
			printf("the coordinate in the country\n");
			break;

		case 8:
			if (destroyHashTable(Atlas) == success) {
				printf(
						"all the memory cleaned and the program is safely closed\n");
				return 0;
			}
			return 1;
			break;

		default:
			printf("please choose a valid number\n");
			break;
		}
	}
	return 1;
}


/*************************************************************************************************
 *This function reads the information from the configuration file and calls to the right functions -
 *add country after that add city and finally sends the new country to the hash table
 *************************************************************************************************/
static status fileRead(const char *path, hashTable Atlas, int hashNumber){
	if( path ==NULL || Atlas == NULL || hashNumber <0)
		return failure;
	int c, i = 1;
	int commaCounter = 0;
	char CountryName[300], CityName[300], FamiliarFood[300], charNumber[300];
	int PopulationNumber, x1, x2, y1, y2, exist = 1;
	Country currentCountry = NULL;

	FILE *configurationFile = NULL;
	configurationFile = fopen(path, "r");
	if (configurationFile) {
		while ((c = getc(configurationFile)) != EOF) {
			if (c == '\t') {
				c = fgetc(configurationFile);
				while (c != '\n') {
					if (commaCounter == 0) {
						CityName[0] = c;
						while ((c = fgetc(configurationFile)) != ',') {
							CityName[i] = (char) c;
							i++;
						}
						CityName[i] = '\0';
						commaCounter++;
						i = 1;
						c = fgetc(configurationFile);
						continue;
					} else if (commaCounter == 1) {
						FamiliarFood[0] = c;
						while ((c = fgetc(configurationFile)) != ',') {
							FamiliarFood[i] = (char) c;
							i++;
						}
						FamiliarFood[i] = '\0';
						commaCounter++;
						i = 1;
						c = fgetc(configurationFile);
						continue;
					} else {
						charNumber[0] = c;
						while ((c = fgetc(configurationFile)) != '\n') {
							charNumber[i] = (char) c;
							i++;
						}
						charNumber[i] = '\0';
						i = 1;
						sscanf(charNumber, "%d", &PopulationNumber);
						commaCounter = 0;
						continue;
					}
				}
				if (currentCountry == NULL)
					continue;
				if (addCity(currentCountry, CityName, FamiliarFood, PopulationNumber)
						== failure){
					freeAllocatedMemoryOfCountry(currentCountry);
					return failure;
				}

			} else {
				while (c != '\n') {
					if (exist == 0) {
						if (addToHashTable(Atlas,CountryName,currentCountry) == failure){
							freeAllocatedMemoryOfCountry(currentCountry);
							return failure;
						}
						freeAllocatedMemoryOfCountry(currentCountry);
						exist = 1;
					}
					if (commaCounter == 0) {
						CountryName[0] = c;
						while ((c = getc(configurationFile)) != ',') {
							CountryName[i] = c;
							i++;
						}
						CountryName[i] = '\0';
						commaCounter++;
						i = 1;
						c = getc(configurationFile);
						continue;
					} else if (commaCounter == 1) {
						charNumber[0] = c;
						while ((c = fgetc(configurationFile)) != ',') {
							charNumber[i] = (char) c;
							i++;
						}
						charNumber[i] = '\0';
						i = 1;
						commaCounter++;
						sscanf(charNumber, "%d", &x1);
						c = fgetc(configurationFile);
						continue;
					} else if (commaCounter == 2) {
						charNumber[0] = c;
						while ((c = fgetc(configurationFile)) != ',') {
							charNumber[i] = (char) c;
							i++;
						}
						charNumber[i] = '\0';
						i = 1;
						commaCounter++;
						sscanf(charNumber, "%d", &y1);
						c = fgetc(configurationFile);
						continue;
					} else if (commaCounter == 3) {
						charNumber[0] = c;
						while ((c = fgetc(configurationFile)) != ',') {
							charNumber[i] = (char) c;
							i++;
						}
						charNumber[i] = '\0';
						i = 1;
						commaCounter++;
						sscanf(charNumber, "%d", &x2);
						c = fgetc(configurationFile);
						continue;
					} else {
						charNumber[0] = c;
						while ((c = fgetc(configurationFile)) != '\n') {
							charNumber[i] = (char) c;
							i++;
						}
						charNumber[i] = '\0';
						i = 1;
						sscanf(charNumber, "%d", &y2);
						commaCounter = 0;
						continue;
					}
				}
				if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)
					continue;
				currentCountry = addCountry(CountryName, x1, y1, x2, y2);
				if (currentCountry == NULL)
					return failure;
				exist = 0;
			}
		}
		if (addToHashTable(Atlas,CountryName,currentCountry) == failure){
			freeAllocatedMemoryOfCountry(currentCountry);
			return failure;
		}
		freeAllocatedMemoryOfCountry(currentCountry);
		fclose(configurationFile);
		return success;
	}
	return failure;
}
