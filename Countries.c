
#include "Countries.h"
/**************************************************************************************
 ******************************STRUCTS DEFENITIONS*************************************
 **************************************************************************************/
//represents the city
struct City {
	char* CityName;
	char* FamiliarFood;
	int PopulationNumber;
};

//represents the geographical area
struct GeographicArea {
	int x1, y1;
	int x2, y2;
};

//represents the country
struct Country {
	char* CountryName;
	GeographicArea GeoArea;
	City* cities;
	int numOfCities;
};



/***************************************************************************************
 *******************************FUNCTIONS IMPLEMENTATION********************************
 **************************************************************************************/

/*adds country by setting its name and geographic area and return pointer to new object*/
Country addCountry(char* countryName, int x1, int y1, int x2, int y2){

	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || countryName == NULL){
		return NULL;
	}

	Country countryToAdd = (Country)malloc(sizeof(struct Country));
	if (countryToAdd == NULL){
		return NULL;
	}

	countryToAdd->CountryName = (char*)malloc(sizeof(char)*(strlen(countryName) + 1));
	if (countryToAdd->CountryName == NULL){
		return NULL;
	}

	countryToAdd->GeoArea = (GeographicArea)malloc(sizeof(struct GeographicArea));
	if (countryToAdd->GeoArea == NULL){
		return NULL;

	}

	strcpy(countryToAdd->CountryName, countryName);
	countryToAdd->GeoArea->x1 = x1;
	countryToAdd->GeoArea->y1 = y1;
	countryToAdd->GeoArea->x2 = x2;
	countryToAdd->GeoArea->y2 = y2;
	countryToAdd->numOfCities = 0;
	countryToAdd->cities = NULL;
	return countryToAdd;
}


/*add city to given country and return true, if the operation didn't succeed return false*/
status addCity (Country CountryToAdd, char* CityName, char* FamiliarFood, int PopulationNum){

	if (CountryToAdd ==NULL ||CityName == NULL || FamiliarFood == NULL || PopulationNum < 0) {
		return failure;
	}

	int index = CountryToAdd->numOfCities;

	CountryToAdd->cities = (City*)realloc(CountryToAdd->cities, (CountryToAdd->numOfCities + 1)*sizeof(City));
	if (CountryToAdd->cities == NULL) //memory allocation failed
		return failure;

	CountryToAdd->cities[index] = (City)malloc(sizeof(struct City));
	if (CountryToAdd->cities[index] == NULL) //memory allocation failed
		return failure;

	CountryToAdd->cities[index]->CityName = (char*)malloc(sizeof(char)*(strlen(CityName) + 1));
	if (CountryToAdd->cities[index]->CityName == NULL) //memory allocation failed
		return failure;

	CountryToAdd->cities[index]->FamiliarFood = (char*)malloc(sizeof(char)*(strlen(FamiliarFood) + 1));
	if (CountryToAdd->cities[index]->FamiliarFood == NULL) //memory allocation failed
		return failure;


	strcpy(CountryToAdd->cities[index]->CityName, CityName);
	strcpy(CountryToAdd->cities[index]->FamiliarFood, FamiliarFood);
	CountryToAdd->cities[index]->PopulationNumber = PopulationNum;
	CountryToAdd->numOfCities++;
	return success;

}


/*remove given city from given country and return true, if the city wasn't found return false*/
status removeCity(Country CountryToRemoveCityFrom, char* CityToRemove){
	if(CountryToRemoveCityFrom ==NULL || CityToRemove ==NULL)
		return failure;
	int index = CountryToRemoveCityFrom->numOfCities;
	for (int i = 0; i < index; i++){
		if (strcmp(CountryToRemoveCityFrom->cities[i]->CityName, CityToRemove) == 0){
			free(CountryToRemoveCityFrom->cities[i]->FamiliarFood);
			CountryToRemoveCityFrom->cities[i]->FamiliarFood = NULL;
			free(CountryToRemoveCityFrom->cities[i]->CityName);
			CountryToRemoveCityFrom->cities[i]->CityName = NULL;
			free(CountryToRemoveCityFrom->cities[i]);
			CountryToRemoveCityFrom->cities[i] = CountryToRemoveCityFrom->cities[index-1];
			CountryToRemoveCityFrom->cities[index-1] = NULL;
			CountryToRemoveCityFrom->numOfCities--;
			return success;
		}
	}
	return failure;
}


/*check if given coordinate is in given country geographic area and return true or false accordingly*/
bool isCoordinateInCountry (Country CountryToSearchIn, int x, int y){
	if (CountryToSearchIn == NULL || x < 0 || y < 0) {
		return false;
	}

	if (x >= CountryToSearchIn->GeoArea->x1 &&
		x <= CountryToSearchIn->GeoArea->x2 &&
		y <= CountryToSearchIn->GeoArea->y1 &&
		y >= CountryToSearchIn->GeoArea->y2)
			return true;

	return false;
}


/*free memory of given country*/
status freeAllocatedMemoryOfCountry(Element CountryToRelease){
	Country givenCountry = (Country)CountryToRelease;
	if(givenCountry == NULL)
		return failure;
	for (int i = 0; i < givenCountry->numOfCities; i++) {
		free(givenCountry->cities[i]->FamiliarFood);
		givenCountry->cities[i]->FamiliarFood = NULL;
		free(givenCountry->cities[i]->CityName);
		givenCountry->cities[i]->CityName = NULL;
		free(givenCountry->cities[i]);
		givenCountry->cities[i] = NULL;
	}
	free (givenCountry->cities);
	givenCountry->cities = NULL;
	free(givenCountry->GeoArea);
	givenCountry->GeoArea = NULL;
	free(givenCountry->CountryName);
	givenCountry->CountryName = NULL;
	free(givenCountry);
	givenCountry = NULL;
	return success;
}


/*deep copy of country object*/
Element deepCopyOfCountryObject(Element givenCountry){
	Country checkCountry = (Country)givenCountry ;
	if (givenCountry ==NULL)
		return NULL;
	Country copyCountry = addCountry(checkCountry->CountryName, checkCountry->GeoArea->x1,
			checkCountry->GeoArea->y1, checkCountry->GeoArea->x2, checkCountry->GeoArea->y2);

	if (copyCountry == NULL){
		return NULL;
	}

	for (int i = 0; i < checkCountry->numOfCities; i++){
		addCity(copyCountry,checkCountry->cities[i]->CityName,
				checkCountry->cities[i]->FamiliarFood,checkCountry->cities[i]->PopulationNumber);
		if(copyCountry->cities[i]==NULL)
			return NULL;
	}
	return copyCountry;
}


/*print country details*/
status printCountry (Element countryToPrint){
	Country givenCountry = (Country)countryToPrint;
	if (givenCountry == NULL)
		return failure;
	printf("Country %s coordinates: <%d,%d> , <%d,%d>\n",
			givenCountry->CountryName, givenCountry->GeoArea->x1,
			givenCountry->GeoArea->y1,
			givenCountry->GeoArea->x2,
			givenCountry->GeoArea->y2);
	for (int i = 0; i < givenCountry->numOfCities; i++) {
		printf("\t%s includes %d residents and their favorite food is %s.\n",
				givenCountry->cities[i]->CityName,
				givenCountry->cities[i]->PopulationNumber,
				givenCountry->cities[i]->FamiliarFood);
	}
	return success;
}


/*check whether city is in given country*/
bool searchCity(Country CountryToSearchIn, char* cityName){
	if (CountryToSearchIn ==NULL || cityName ==NULL)
		return false;
	for (int i = 0; i < CountryToSearchIn->numOfCities; i++){
		if (strcmp(CountryToSearchIn->cities[i]->CityName, cityName) == 0){
			return true;
		}
	}
	return false;
}


//copies the country name
Element copyCountryName(Element countryName){
	char *givenCountry = (char*)countryName;
	if (givenCountry ==NULL)
		return NULL;
	char *copyCountryName= (char*) malloc (sizeof(char)*(strlen(givenCountry)+1));
	if (copyCountryName == NULL)
		return NULL;
	strcpy(copyCountryName,givenCountry);
	return copyCountryName;
}


//frees the country name memory
status freeCountryName(Element countryName){
	if (countryName ==NULL)
		return failure;
	free(countryName);
	countryName = NULL;
	return success;
}


//prints the name of the country
status prinCountryName(Element countryName){
	if (countryName ==NULL)
		return failure;
	printf("%s\n", (char*)countryName);
	return success;
}


//converts a country name to a number according to its ascii number
int transformCountryIntoNumberFunction(Element countryName) {
	if (countryName == NULL)
		return 0;
	int asciiNumebr = 0;
	for (int i = 0; i < strlen((char*)countryName); i++) {
		asciiNumebr += (int)((char*)countryName)[i];
	}
	return asciiNumebr;
}


//checks if two countries are equal according to their name
bool isEqualCountry(Element firstCountryName, Element secondCountryName){
	if (firstCountryName == NULL || secondCountryName ==NULL)
		return false;
	if (strcmp((char*)firstCountryName,(char*)secondCountryName)==0)
		return true;
	return false;
}






