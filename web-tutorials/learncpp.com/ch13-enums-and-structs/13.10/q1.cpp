// You are running a website, and you are trying to calculate your advertising revenue. Write a program that allows you to enter 3 pieces of data:

// How many ads were watched.
// What percentage of users clicked on an ad.
// The average earnings per clicked ad.
// Store those 3 values in a struct. Pass that struct to another function that prints each of the values. 

// The print function should also print how much you made for that day (multiply the 3 fields together).

#include <iostream>

struct Metrics
{
    int adsWatched{ };
    double percentClickedAds{ };
    double earningsPerAd{ }; 
};

void printStruct(Metrics metric) 
{
    std::cout << "Ads watched: " << metric.adsWatched << '\n'
              << "Percent of users who clicked ads: " << metric.percentClickedAds << '\n'
              << "Earnings of the day: $" << metric.earningsPerAd * metric.adsWatched * metric.percentClickedAds << '\n';
}

int main()
{
    Metrics metric;
    std::cin >> metric.adsWatched >> metric.percentClickedAds >> metric.earningsPerAd;

    printStruct(metric);

    return 0;
}