#pragma once
#include <iostream>
#include <string>
using namespace std;

// Forward declarations
class Seller;
class Buyer;
class Vehicle;
class Admin;

// ============================================================
// CLASS 1: Address (used via Composition in User)
// ============================================================
class Address {
private:
    string street;
    string city;
    string province;
    string postalCode;
    const string country; // constant data member

public:
    // Default constructor
    Address() : street(""), city(""), province(""), postalCode(""), country("Pakistan") {}

    // Parameterized constructor
    Address(string st, string ct, string prov, string postal)
        : street(st), city(ct), province(prov), postalCode(postal), country("Pakistan") {}

    // Copy constructor
    Address(const Address& other)
        : street(other.street), city(other.city), province(other.province),
          postalCode(other.postalCode), country(other.country) {}

    // Assignment operator (needed because of const member; country is preserved from current object)
    Address& operator=(const Address& other) {
        if (this != &other) {
            street = other.street;
            city = other.city;
            province = other.province;
            postalCode = other.postalCode;
            // const country cannot be reassigned - it keeps its original value
        }
        return *this;
    }

    // Getters
    string getStreet()     const { return street; }
    string getCity()       const { return city; }
    string getProvince()   const { return province; }
    string getPostalCode() const { return postalCode; }
    string getCountry()    const { return country; }

    // Setters
    void setStreet(string s)     { street = s; }
    void setCity(string c)       { city = c; }
    void setProvince(string p)   { province = p; }
    void setPostalCode(string p) { postalCode = p; }

    // Member functions
    void display() const {
        cout << street << ", " << city << ", " << province
             << " - " << postalCode << ", " << country << endl;
    }

    bool isValidPostalCode() const { return postalCode.length() == 5; }
    string getFullAddress() const { return street + ", " + city + ", " + province; }

    bool isSameCity(const Address& other) const { return city == other.city; }
};

// ============================================================
// CLASS 2: ContactInfo (used via Composition in User)
// ============================================================
class ContactInfo {
private:
    string phoneNumber;
    string email;
    bool whatsappEnabled;
    string alternatePhone;
    const string platformCode; // constant

public:
    // Default constructor
    ContactInfo() : phoneNumber(""), email(""), whatsappEnabled(false),
                    alternatePhone(""), platformCode("PW") {}

    // Parameterized constructor
    ContactInfo(string phone, string em, bool wa)
        : phoneNumber(phone), email(em), whatsappEnabled(wa),
          alternatePhone(""), platformCode("PW") {}

    // Copy constructor
    ContactInfo(const ContactInfo& other)
        : phoneNumber(other.phoneNumber), email(other.email),
          whatsappEnabled(other.whatsappEnabled), alternatePhone(other.alternatePhone),
          platformCode(other.platformCode) {}

    // Assignment operator (needed because of const member)
    ContactInfo& operator=(const ContactInfo& other) {
        if (this != &other) {
            phoneNumber = other.phoneNumber;
            email = other.email;
            whatsappEnabled = other.whatsappEnabled;
            alternatePhone = other.alternatePhone;
            // const platformCode cannot be reassigned
        }
        return *this;
    }

    // Getters / Setters
    string getPhone()     const { return phoneNumber; }
    string getEmail()     const { return email; }
    bool   isWhatsapp()   const { return whatsappEnabled; }
    void setPhone(string p)     { phoneNumber = p; }
    void setEmail(string e)     { email = e; }
    void setWhatsapp(bool w)    { whatsappEnabled = w; }

    // Member functions
    void display() const {
        cout << "Phone: " << phoneNumber << " | Email: " << email;
        if (whatsappEnabled) cout << " | WhatsApp: Available";
        cout << endl;
    }

    bool isValidEmail() const {
        return email.find('@') != string::npos && email.find('.') != string::npos;
    }

    bool isContactable() const { return !phoneNumber.empty() || !email.empty(); }

    string getPrimaryContact() const {
        return whatsappEnabled ? "WhatsApp: " + phoneNumber : "Phone: " + phoneNumber;
    }
};

// ============================================================
// CLASS 3: Message (Aggregation - Buyer & Seller referenced)
// ============================================================
class Message {
private:
    int messageId;
    string senderName;
    string receiverName;
    string content;
    string timestamp;
    bool isRead;

    static int messageCount; // Static member - tracks total messages sent on platform

public:
    // Default constructor
    Message() : messageId(0), senderName(""), receiverName(""),
                content(""), timestamp(""), isRead(false) {}

    // Parameterized constructor
    Message(int id, string sender, string receiver, string msg, string time)
        : messageId(id), senderName(sender), receiverName(receiver),
          content(msg), timestamp(time), isRead(false) {
        messageCount++;
    }

    // Getters / Setters
    int    getId()           const { return messageId; }
    string getSender()       const { return senderName; }
    string getReceiver()     const { return receiverName; }
    string getContent()      const { return content; }
    string getTimestamp()    const { return timestamp; }
    bool   getIsRead()       const { return isRead; }
    void   markAsRead()            { isRead = true; }

    // Static function - reason: returns platform-wide count, not tied to any instance
    static int getTotalMessages() { return messageCount; }
    static void resetCount()      { messageCount = 0; }

    // Member functions
    void display() const {
        cout << "[" << timestamp << "] From: " << senderName
             << " -> To: " << receiverName << endl;
        cout << "  Message: " << content << (isRead ? " [Read]" : " [Unread]") << endl;
    }

    bool containsKeyword(const string& kw) const { return content.find(kw) != string::npos; }
    string getSummary() const { return senderName + ": " + content.substr(0, 50); }
};

int Message::messageCount = 0;

// ============================================================
// CLASS 4: Vehicle (Core class, used in Listing via Composition)
// ============================================================
class Vehicle {
private:
    string brand;
    string model;
    int    year;
    double price;
    int    mileage;
    string color;

    static int totalVehiclesListed; // Static - platform-wide counter

public:
    // Default constructor
    Vehicle() : brand(""), model(""), year(0), price(0.0), mileage(0), color("") {}

    // Parameterized constructor
    Vehicle(string br, string mo, int yr, double pr, int mi, string col)
        : brand(br), model(mo), year(yr), price(pr), mileage(mi), color(col) {
        totalVehiclesListed++;
    }

    // Copy constructor
    Vehicle(const Vehicle& v)
        : brand(v.brand), model(v.model), year(v.year),
          price(v.price), mileage(v.mileage), color(v.color) {}

    // Getters
    string getBrand()  const { return brand; }
    string getModel()  const { return model; }
    int    getYear()   const { return year; }
    double getPrice()  const { return price; }
    int    getMileage()const { return mileage; }
    string getColor()  const { return color; }

    // Setters
    void setBrand(string b)  { brand = b; }
    void setModel(string m)  { model = m; }
    void setYear(int y)      { year = y; }
    void setPrice(double p)  { price = p; }
    void setMileage(int m)   { mileage = m; }
    void setColor(string c)  { color = c; }

    // Static function - reason: total count belongs to the class, not to an instance
    static int getTotalVehicles() { return totalVehiclesListed; }

    // Member functions
    void display() const {
        cout << year << " " << brand << " " << model
             << " | Price: PKR " << price
             << " | Mileage: " << mileage << " km"
             << " | Color: " << color << endl;
    }

    bool matchesBrand(const string& b)  const { return brand == b; }
    bool matchesModel(const string& m)  const { return model == m; }
    bool isPriceInRange(double lo, double hi) const { return price >= lo && price <= hi; }
    bool isYearInRange(int lo, int hi)  const { return year >= lo && year <= hi; }
};

int Vehicle::totalVehiclesListed = 0;

// ============================================================
// CLASS 5: CarSpecifications (used via Composition in Listing)
// ============================================================
class CarSpecifications {
private:
    string engineType;      // Petrol, Diesel, Hybrid, Electric
    string transmission;    // Manual, Automatic
    int    engineCC;
    string registrationCity;
    const int   modelYear;  // constant - set at object creation, never changes
    string condition;       // New / Used

public:
    // Default constructor - uses constant member, must be initialized in init list
    CarSpecifications() : engineType(""), transmission(""), engineCC(0),
                          registrationCity(""), modelYear(0), condition("") {}

    // Parameterized constructor
    CarSpecifications(string eng, string trans, int cc, string regCity, int yr, string cond)
        : engineType(eng), transmission(trans), engineCC(cc),
          registrationCity(regCity), modelYear(yr), condition(cond) {}

    // Copy constructor
    CarSpecifications(const CarSpecifications& s)
        : engineType(s.engineType), transmission(s.transmission), engineCC(s.engineCC),
          registrationCity(s.registrationCity), modelYear(s.modelYear), condition(s.condition) {}

    // Assignment operator (needed because of const modelYear)
    CarSpecifications& operator=(const CarSpecifications& s) {
        if (this != &s) {
            engineType = s.engineType;
            transmission = s.transmission;
            engineCC = s.engineCC;
            registrationCity = s.registrationCity;
            condition = s.condition;
            // const modelYear cannot be reassigned
        }
        return *this;
    }

    // Getters
    string getEngineType()       const { return engineType; }
    string getTransmission()     const { return transmission; }
    int    getEngineCC()         const { return engineCC; }
    string getRegistrationCity() const { return registrationCity; }
    int    getModelYear()        const { return modelYear; }
    string getCondition()        const { return condition; }

    // Setters (modelYear is const - no setter)
    void setEngineType(string e)       { engineType = e; }
    void setTransmission(string t)     { transmission = t; }
    void setEngineCC(int cc)           { engineCC = cc; }
    void setRegistrationCity(string c) { registrationCity = c; }
    void setCondition(string c)        { condition = c; }

    // Constant function - does not modify object
    void display() const {
        cout << "Engine: " << engineType << " (" << engineCC << "cc) | "
             << "Trans: " << transmission << " | "
             << "Reg: " << registrationCity << " | "
             << "Condition: " << condition << endl;
    }

    bool isAutomatic()   const { return transmission == "Automatic"; }
    bool isElectric()    const { return engineType == "Electric"; }
    string getSummary()  const { return engineType + " " + to_string(engineCC) + "cc " + transmission; }
};

// ============================================================
// CLASS 6: Listing (COMPOSITION: owns Vehicle + CarSpecifications)
// ============================================================
class Listing {
private:
    int       listingId;
    Vehicle   vehicle;          // COMPOSITION - Vehicle's lifetime tied to Listing
    CarSpecifications specs;    // COMPOSITION - Specs lifetime tied to Listing
    string    description;
    string    status;           // Pending, Approved, Rejected, Sold
    string    postedDate;
    string    sellerUsername;

public:
    // Default constructor
    Listing() : listingId(0), vehicle(), specs(), description(""),
                status("Pending"), postedDate(""), sellerUsername("") {}

    // Parameterized constructor
    Listing(int id, Vehicle v, CarSpecifications s, string desc,
            string date, string seller)
        : listingId(id), vehicle(v), specs(s), description(desc),
          status("Pending"), postedDate(date), sellerUsername(seller) {}

    // Getters / Setters
    int         getId()           const { return listingId; }
    Vehicle     getVehicle()      const { return vehicle; }
    CarSpecifications getSpecs()  const { return specs; }
    string      getStatus()       const { return status; }
    string      getSellerName()   const { return sellerUsername; }
    string      getPostedDate()   const { return postedDate; }
    void setStatus(string s)            { status = s; }
    void setDescription(string d)       { description = d; }

    // Member functions
    void display() const {
        cout << "--- Listing #" << listingId << " [" << status << "] ---" << endl;
        vehicle.display();
        specs.display();
        cout << "Description: " << description << endl;
        cout << "Seller: " << sellerUsername << " | Posted: " << postedDate << endl;
    }

    bool isApproved()  const { return status == "Approved"; }
    bool isPending()   const { return status == "Pending"; }
    bool matchesBrand(const string& b) const { return vehicle.matchesBrand(b); }
    bool matchesPriceRange(double lo, double hi) const { return vehicle.isPriceInRange(lo, hi); }
};

// ============================================================
// CLASS 7: User (Base / abstract concept; Seller & Buyer extend it)
// ============================================================
class User {
protected:
    string     username;
    string     passwordHash;
    ContactInfo contact;  // COMPOSITION - ContactInfo lifetime tied to User
    Address     address;  // COMPOSITION - Address lifetime tied to User
    string     userType;
    bool       isVerified;

public:
    // Default constructor
    User() : username(""), passwordHash(""), contact(), address(),
             userType(""), isVerified(false) {}

    // Parameterized constructor
    User(string uname, string pwd, ContactInfo ci, Address addr, string type)
        : username(uname), passwordHash(pwd), contact(ci), address(addr),
          userType(type), isVerified(false) {}

    // Getters / Setters
    string getUsername()   const { return username; }
    string getUserType()   const { return userType; }
    bool   getIsVerified() const { return isVerified; }
    ContactInfo getContact() const { return contact; }
    Address     getAddress() const { return address; }
    void setUsername(string u)     { username = u; }
    void verify()                  { isVerified = true; }

    // Member functions
    virtual void displayProfile() const {
        cout << "=== " << userType << " Profile ===" << endl;
        cout << "Username: " << username << (isVerified ? " [Verified]" : "") << endl;
        contact.display();
        address.display();
    }

    bool isLoggedIn() const { return !username.empty(); }
    bool hasValidContact() const { return contact.isContactable(); }
    string getDisplayName() const { return username + " (" + userType + ")"; }
};

// ============================================================
// CLASS 8: Seller (inherits User; AGGREGATION with Listing array)
// ============================================================
class Seller : public User {
private:
    Listing*  listings[50];   // AGGREGATION - Seller references Listing objects (not owns exclusively)
    int       listingCount;
    int       totalSales;
    double    totalRevenue;
    string    sellerRating;   // e.g. "4.5/5"

public:
    // Default constructor
    Seller() : User(), listingCount(0), totalSales(0), totalRevenue(0.0), sellerRating("0/5") {
        for (int i = 0; i < 50; i++) listings[i] = nullptr;
    }

    // Parameterized constructor
    Seller(string uname, string pwd, ContactInfo ci, Address addr)
        : User(uname, pwd, ci, addr, "Seller"),
          listingCount(0), totalSales(0), totalRevenue(0.0), sellerRating("5/5") {
        for (int i = 0; i < 50; i++) listings[i] = nullptr;
    }

    // Getters / Setters
    int    getListingCount() const { return listingCount; }
    int    getTotalSales()   const { return totalSales; }
    double getTotalRevenue() const { return totalRevenue; }
    string getRating()       const { return sellerRating; }
    void   setRating(string r)     { sellerRating = r; }

    // Add a listing (Aggregation: Seller points to Listing, does not own it)
    void addListing(Listing* l) {
        if (listingCount < 50) {
            listings[listingCount++] = l;
            cout << "Listing added by " << username << endl;
        }
    }

    // Remove listing by ID
    void removeListing(int id) {
        for (int i = 0; i < listingCount; i++) {
            if (listings[i] && listings[i]->getId() == id) {
                for (int j = i; j < listingCount - 1; j++) listings[j] = listings[j+1];
                listings[--listingCount] = nullptr;
                cout << "Listing #" << id << " removed." << endl;
                return;
            }
        }
        cout << "Listing not found." << endl;
    }

    // Display all listings
    void viewMyListings() const {
        cout << "=== Listings by " << username << " ===" << endl;
        for (int i = 0; i < listingCount; i++) {
            if (listings[i]) listings[i]->display();
        }
    }

    void recordSale(double amount) {
        totalSales++;
        totalRevenue += amount;
    }

    void displayProfile() const override {
        User::displayProfile();
        cout << "Total Listings: " << listingCount << " | Sales: " << totalSales
             << " | Revenue: PKR " << totalRevenue << " | Rating: " << sellerRating << endl;
    }
};

// ============================================================
// CLASS 9: Buyer (inherits User; AGGREGATION with Listing favorites)
// ============================================================
class Buyer : public User {
private:
    Listing*  favorites[20];  // AGGREGATION - Buyer references Listings (not owns them)
    int       favCount;
    Message   inbox[100];     // Array of objects (composition with messages)
    int       inboxCount;
    double    budget;
    string    preferredCity;

public:
    // Default constructor
    Buyer() : User(), favCount(0), inboxCount(0), budget(0.0), preferredCity("") {
        for (int i = 0; i < 20; i++) favorites[i] = nullptr;
    }

    // Parameterized constructor
    Buyer(string uname, string pwd, ContactInfo ci, Address addr, double bud)
        : User(uname, pwd, ci, addr, "Buyer"),
          favCount(0), inboxCount(0), budget(bud), preferredCity(addr.getCity()) {
        for (int i = 0; i < 20; i++) favorites[i] = nullptr;
    }

    // Getters / Setters
    double getBudget()         const { return budget; }
    string getPreferredCity()  const { return preferredCity; }
    int    getFavCount()       const { return favCount; }
    void   setBudget(double b)       { budget = b; }
    void   setPreferredCity(string c){ preferredCity = c; }

    // Save listing to favorites (Aggregation)
    void saveFavorite(Listing* l) {
        if (favCount < 20) {
            favorites[favCount++] = l;
            cout << "Listing saved to favorites!" << endl;
        }
    }

    // Remove from favorites
    void removeFavorite(int listingId) {
        for (int i = 0; i < favCount; i++) {
            if (favorites[i] && favorites[i]->getId() == listingId) {
                for (int j = i; j < favCount - 1; j++) favorites[j] = favorites[j+1];
                favorites[--favCount] = nullptr;
                cout << "Removed from favorites." << endl;
                return;
            }
        }
    }

    // Send message to seller
    void sendMessage(const string& sellerName, const string& content, const string& time) {
        if (inboxCount < 100) {
            int id = inboxCount + 1;
            inbox[inboxCount++] = Message(id, username, sellerName, content, time);
            cout << "Message sent to " << sellerName << endl;
        }
    }

    void viewFavorites() const {
        cout << "=== " << username << "'s Favorites ===" << endl;
        for (int i = 0; i < favCount; i++) {
            if (favorites[i]) favorites[i]->display();
        }
    }

    void viewInbox() const {
        cout << "=== " << username << "'s Messages ===" << endl;
        for (int i = 0; i < inboxCount; i++) inbox[i].display();
    }

    void displayProfile() const override {
        User::displayProfile();
        cout << "Budget: PKR " << budget << " | Favorites: " << favCount
             << " | Preferred City: " << preferredCity << endl;
    }
};

// ============================================================
// CLASS 10: Admin
// ============================================================
class Admin : public User {
private:
    string    adminLevel;     // SuperAdmin, Moderator
    int       approvedCount;
    int       rejectedCount;
    string    department;
    const string adminCode;   // constant - assigned at creation

public:
    // Default constructor - const member needs init list
    Admin() : User(), adminLevel(""), approvedCount(0),
              rejectedCount(0), department(""), adminCode("ADM000") {}

    // Parameterized constructor
    Admin(string uname, string pwd, ContactInfo ci, Address addr, string level, string code)
        : User(uname, pwd, ci, addr, "Admin"),
          adminLevel(level), approvedCount(0), rejectedCount(0),
          department("Moderation"), adminCode(code) {}

    // Assignment operator (needed because of const adminCode)
    Admin& operator=(const Admin& other) {
        if (this != &other) {
            User::operator=(other);
            adminLevel = other.adminLevel;
            approvedCount = other.approvedCount;
            rejectedCount = other.rejectedCount;
            department = other.department;
            // const adminCode cannot be reassigned
        }
        return *this;
    }

    // Getters
    string getAdminLevel() const { return adminLevel; }
    string getAdminCode()  const { return adminCode; }
    int getApprovedCount() const { return approvedCount; }
    int getRejectedCount() const { return rejectedCount; }

    // Approve a listing
    void approveListing(Listing& l) {
        l.setStatus("Approved");
        approvedCount++;
        cout << "Admin " << username << " approved listing #" << l.getId() << endl;
    }

    // Reject a listing
    void rejectListing(Listing& l, const string& reason) {
        l.setStatus("Rejected");
        rejectedCount++;
        cout << "Admin " << username << " rejected listing #" << l.getId()
             << " | Reason: " << reason << endl;
    }

    // Constant function: view stats without modifying state
    void viewStats() const {
        cout << "Admin: " << username << " | Level: " << adminLevel << endl;
        cout << "Approved: " << approvedCount << " | Rejected: " << rejectedCount << endl;
    }

    void displayProfile() const override {
        User::displayProfile();
        cout << "Level: " << adminLevel << " | Code: " << adminCode
             << " | Dept: " << department << endl;
        viewStats();
    }
};

// ============================================================
// CLASS 11: SearchFilter (utility class for filtering listings)
// ============================================================
class SearchFilter {
private:
    string brand;
    string model;
    double minPrice;
    double maxPrice;
    int    minYear;
    int    maxYear;
    int    maxMileage;
    string city;
    const int MAX_RESULTS = 50; // constant

public:
    // Default constructor
    SearchFilter() : brand(""), model(""), minPrice(0), maxPrice(999999999),
                     minYear(2000), maxYear(2026), maxMileage(999999), city("") {}

    // Parameterized constructor
    SearchFilter(string br, string mo, double lo, double hi, int yrLo, int yrHi)
        : brand(br), model(mo), minPrice(lo), maxPrice(hi),
          minYear(yrLo), maxYear(yrHi), maxMileage(999999), city("") {}

    // Getters / Setters
    void setBrand(string b)    { brand = b; }
    void setModel(string m)    { model = m; }
    void setPriceRange(double lo, double hi) { minPrice = lo; maxPrice = hi; }
    void setYearRange(int lo, int hi)        { minYear = lo; maxYear = hi; }
    void setMaxMileage(int m)  { maxMileage = m; }
    void setCity(string c)     { city = c; }

    // Check if a listing matches filter
    bool matches(const Listing& l) const {
        const Vehicle& v = l.getVehicle();
        if (!brand.empty() && !v.matchesBrand(brand)) return false;
        if (!model.empty() && !v.matchesModel(model)) return false;
        if (!v.isPriceInRange(minPrice, maxPrice)) return false;
        if (!v.isYearInRange(minYear, maxYear)) return false;
        return true;
    }

    void display() const {
        cout << "Filter: Brand=" << brand << " Model=" << model
             << " Price=[" << minPrice << "-" << maxPrice << "]"
             << " Year=[" << minYear << "-" << maxYear << "]" << endl;
    }

    void resetFilter() {
        brand = ""; model = ""; minPrice = 0; maxPrice = 999999999;
        minYear = 2000; maxYear = 2026; maxMileage = 999999; city = "";
    }

    bool hasAnyFilter() const {
        return !brand.empty() || !model.empty() || minPrice > 0 || maxPrice < 999999999;
    }
};

// ============================================================
// CLASS 12: Marketplace (main system class - Array of Objects)
// ============================================================
class Marketplace {
private:
    Listing  listings[200];     // Array of Objects
    int      listingCount;
    Seller   sellers[100];      // Array of Objects
    int      sellerCount;
    Buyer    buyers[100];       // Array of Objects
    int      buyerCount;
    const string platformName;  // constant

    static int totalTransactions; // Static - platform-wide counter

public:
    // Default constructor - const member needs init list
    Marketplace() : listingCount(0), sellerCount(0), buyerCount(0),
                    platformName("PakWheels Clone") {
    }

    // Add listing
    void addListing(const Listing& l) {
        if (listingCount < 200) {
            listings[listingCount++] = l;
            cout << "Listing added to marketplace." << endl;
        }
    }

    // Delete listing by ID
    void deleteListing(int id) {
        for (int i = 0; i < listingCount; i++) {
            if (listings[i].getId() == id) {
                for (int j = i; j < listingCount - 1; j++) listings[j] = listings[j+1];
                listingCount--;
                cout << "Listing #" << id << " deleted." << endl;
                return;
            }
        }
        cout << "Listing not found." << endl;
    }

    // Update listing status
    void updateListingStatus(int id, const string& status) {
        for (int i = 0; i < listingCount; i++) {
            if (listings[i].getId() == id) {
                listings[i].setStatus(status);
                cout << "Listing #" << id << " updated to: " << status << endl;
                return;
            }
        }
    }

    // Search listings using SearchFilter
    void searchListings(const SearchFilter& filter) const {
        cout << "\n=== Search Results ===" << endl;
        int found = 0;
        for (int i = 0; i < listingCount; i++) {
            if (filter.matches(listings[i])) {
                listings[i].display();
                found++;
            }
        }
        if (found == 0) cout << "No listings match your criteria." << endl;
        else cout << found << " listing(s) found." << endl;
    }

    // Display all approved listings
    void displayApprovedListings() const {
        cout << "\n=== Available Vehicles ===" << endl;
        for (int i = 0; i < listingCount; i++) {
            if (listings[i].isApproved()) listings[i].display();
        }
    }

    // Register seller
    void registerSeller(const Seller& s) {
        if (sellerCount < 100) sellers[sellerCount++] = s;
    }

    // Register buyer
    void registerBuyer(const Buyer& b) {
        if (buyerCount < 100) buyers[buyerCount++] = b;
    }

    // Static function - platform-wide transaction count
    static void recordTransaction() { totalTransactions++; }
    static int  getTotalTransactions() { return totalTransactions; }

    // Get platform name (const function)
    string getPlatformName() const { return platformName; }

    void displayStats() const {
        cout << "=== " << platformName << " Stats ===" << endl;
        cout << "Listings: " << listingCount << " | Sellers: " << sellerCount
             << " | Buyers: " << buyerCount << endl;
        cout << "Total Vehicles Listed: " << Vehicle::getTotalVehicles() << endl;
        cout << "Total Messages Sent: " << Message::getTotalMessages() << endl;
        cout << "Total Transactions: " << totalTransactions << endl;
    }
};

int Marketplace::totalTransactions = 0;
