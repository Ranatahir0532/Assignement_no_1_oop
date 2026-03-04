#include "CarMarketplace.h"
#include <iostream>
using namespace std;

void printSeparator(const string& title = "") {
    cout << "\n========================================" << endl;
    if (!title.empty()) cout << "  " << title << endl;
    cout << "========================================" << endl;
}

int main() {
    printSeparator("PakWheels-Style Car Marketplace System");

    // -------------------------------------------------------
    // 1. Create Marketplace
    // -------------------------------------------------------
    Marketplace market;

    // -------------------------------------------------------
    // 2. Create Sellers (Parameterized constructors)
    // -------------------------------------------------------
    ContactInfo sellerContact("0300-1234567", "ahmed@email.com", true);
    Address sellerAddress("House 12, DHA Phase 5", "Karachi", "Sindh", "75500");
    Seller seller1("ahmed_autos", "pass123", sellerContact, sellerAddress);
    market.registerSeller(seller1);

    ContactInfo seller2Contact("0321-9876543", "cars@lahore.com", false);
    Address seller2Address("Main Boulevard", "Lahore", "Punjab", "54000");
    Seller seller2("lahore_motors", "pass456", seller2Contact, seller2Address);
    market.registerSeller(seller2);

    // -------------------------------------------------------
    // 3. Create Buyers (Parameterized constructors)
    // -------------------------------------------------------
    ContactInfo buyerContact("0312-5555555", "buyer@gmail.com", true);
    Address buyerAddress("Clifton Block 4", "Karachi", "Sindh", "75600");
    Buyer buyer1("zain_buyer", "buypass", buyerContact, buyerAddress, 2500000.0);
    market.registerBuyer(buyer1);

    // -------------------------------------------------------
    // 4. Create Admin
    // -------------------------------------------------------
    ContactInfo adminContact("0333-0000001", "admin@pakwheels.pk", false);
    Address adminAddress("I.I Chundrigar Road", "Karachi", "Sindh", "74000");
    Admin admin1("super_admin", "admin123", adminContact, adminAddress, "SuperAdmin", "ADM001");

    // -------------------------------------------------------
    // 5. Create Vehicles and Listings
    // -------------------------------------------------------
    printSeparator("Creating Vehicle Listings");

    // Listing 1
    Vehicle v1("Toyota", "Corolla", 2020, 2800000, 45000, "White");
    CarSpecifications s1("Petrol", "Automatic", 1800, "Karachi", 2020, "Used");
    Listing l1(1, v1, s1, "Excellent condition, 1 owner, full service history", "2026-03-01", "ahmed_autos");

    // Listing 2
    Vehicle v2("Honda", "Civic", 2022, 4200000, 22000, "Silver");
    CarSpecifications s2("Petrol", "Automatic", 1500, "Lahore", 2022, "Used");
    Listing l2(2, v2, s2, "Turbo variant, almost new", "2026-03-02", "lahore_motors");

    // Listing 3
    Vehicle v3("Suzuki", "Alto", 2021, 1600000, 38000, "Red");
    CarSpecifications s3("Petrol", "Manual", 660, "Karachi", 2021, "Used");
    Listing l3(3, v3, s3, "Good fuel economy, perfect city car", "2026-03-02", "ahmed_autos");

    // Listing 4
    Vehicle v4("Toyota", "Yaris", 2023, 3100000, 10000, "Black");
    CarSpecifications s4("Hybrid", "Automatic", 1500, "Islamabad", 2023, "Used");
    Listing l4(4, v4, s4, "Hybrid variant, very low mileage", "2026-03-03", "lahore_motors");

    // Listing 5
    Vehicle v5("Kia", "Sportage", 2021, 5500000, 55000, "Blue");
    CarSpecifications s5("Petrol", "Automatic", 2000, "Karachi", 2021, "Used");
    Listing l5(5, v5, s5, "AWD, panoramic roof, premium sound", "2026-03-03", "ahmed_autos");

    // Add to marketplace
    market.addListing(l1);
    market.addListing(l2);
    market.addListing(l3);
    market.addListing(l4);
    market.addListing(l5);

    // Add to seller's personal list
    seller1.addListing(&l1);
    seller1.addListing(&l3);
    seller1.addListing(&l5);
    seller2.addListing(&l2);
    seller2.addListing(&l4);

    // -------------------------------------------------------
    // 6. Admin approves/rejects listings
    // -------------------------------------------------------
    printSeparator("Admin Moderation");

    admin1.approveListing(l1);
    admin1.approveListing(l2);
    admin1.approveListing(l3);
    admin1.approveListing(l4);
    admin1.rejectListing(l5, "Incomplete documentation");
    admin1.viewStats();

    // Update approved status in marketplace too
    market.updateListingStatus(1, "Approved");
    market.updateListingStatus(2, "Approved");
    market.updateListingStatus(3, "Approved");
    market.updateListingStatus(4, "Approved");
    market.updateListingStatus(5, "Rejected");

    // -------------------------------------------------------
    // 7. Display all approved listings
    // -------------------------------------------------------
    market.displayApprovedListings();

    // -------------------------------------------------------
    // 8. Buyer searches and filters
    // -------------------------------------------------------
    printSeparator("Buyer Searching Vehicles");

    // Search by brand
    SearchFilter filter1;
    filter1.setBrand("Toyota");
    cout << "\n>> Search: Toyota vehicles" << endl;
    market.searchListings(filter1);

    // Search by price range
    SearchFilter filter2;
    filter2.setPriceRange(1000000, 3000000);
    cout << "\n>> Search: Budget PKR 1M - 3M" << endl;
    market.searchListings(filter2);

    // Search by year range
    SearchFilter filter3;
    filter3.setYearRange(2022, 2026);
    cout << "\n>> Search: 2022 or newer" << endl;
    market.searchListings(filter3);

    // -------------------------------------------------------
    // 9. Buyer saves favorites
    // -------------------------------------------------------
    printSeparator("Buyer Saves Favorites");

    buyer1.saveFavorite(&l1);
    buyer1.saveFavorite(&l4);
    buyer1.viewFavorites();

    // -------------------------------------------------------
    // 10. Buyer sends message to seller
    // -------------------------------------------------------
    printSeparator("Buyer Sends Message to Seller");

    buyer1.sendMessage("ahmed_autos", "Hi! Is the Corolla still available? Can I negotiate the price?", "2026-03-04 10:30");
    buyer1.sendMessage("lahore_motors", "Interested in the Yaris Hybrid. Can we schedule a test drive?", "2026-03-04 11:00");
    buyer1.viewInbox();

    // -------------------------------------------------------
    // 11. Seller views and deletes a listing
    // -------------------------------------------------------
    printSeparator("Seller Operations");

    cout << "\n>> Seller's listings before deletion:" << endl;
    seller1.viewMyListings();

    seller1.removeListing(3); // remove Suzuki Alto
    market.deleteListing(3);

    cout << "\n>> Seller's listings after deletion:" << endl;
    seller1.viewMyListings();

    // -------------------------------------------------------
    // 12. Display user profiles
    // -------------------------------------------------------
    printSeparator("User Profiles");

    seller1.displayProfile();
    cout << endl;
    buyer1.displayProfile();
    cout << endl;
    admin1.displayProfile();

    // -------------------------------------------------------
    // 13. Record a transaction (static member)
    // -------------------------------------------------------
    printSeparator("Platform Statistics");

    Marketplace::recordTransaction();
    Marketplace::recordTransaction();

    market.displayStats();

    // -------------------------------------------------------
    // 14. Demonstrate copy constructor
    // -------------------------------------------------------
    printSeparator("Copy Constructor Demo");

    Vehicle v1Copy(v1); // Copy constructor
    cout << "Original: "; v1.display();
    cout << "Copy:     "; v1Copy.display();

    Address addrCopy(sellerAddress); // Copy constructor
    cout << "Original address: "; sellerAddress.display();
    cout << "Copied address:   "; addrCopy.display();

    cout << "\n=== Program Completed Successfully ===" << endl;

    return 0;
}
