#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Room {
public:
    int roomNumber;
    bool isBooked;

    Room(int number) : roomNumber(number), isBooked(false) {}
};

class Booking {
public:
    int bookingId;
    int roomNumber;
    string guestName;

    Booking(int id, int room, const string& name) : bookingId(id), roomNumber(room), guestName(name) {}
};

class MenuItem {
public:
    string name;
    double price;

    MenuItem(string n, double p) : name(n), price(p) {}
};

class Order {
public:
    vector<MenuItem> items;

    void addItem(const MenuItem& item) {
        items.push_back(item);
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.price;
        }
        return total;
    }

    void displayOrder() const {
        cout << "Order Details:\n";
        for (const auto& item : items) {
            cout << item.name << "\tRs." << item.price << endl;
        }
        cout << "-----------------------\n";
        cout << "Total: Rs." << calculateTotal() << endl;
    }
};

class RoomService {
public:
    void placeOrder(Order& order) {
        orders.push_back(order);
        cout << "Order placed Successfully!\n";
    }

    void viewOrders() const {
        if (orders.empty()) {
            cout << "No orders yet.\n";
        } else {
            cout << "Current Orders:\n";
            for (const auto& order : orders) {

                order.displayOrder();
                cout << "-----------------------\n";
            }
        }
    }

private:
    vector<Order> orders;
};

class Hotel {
private:
    vector<Room> rooms;
    vector<Booking> bookings;
    vector<string> complaints;
    int nextBookingId;

public:
    Hotel(int numRooms) : nextBookingId(1) {
        for (int i = 1; i <= numRooms; ++i) {
            rooms.push_back(Room(i));
        }
    }

    void displayAvailableRooms() const {
        cout << "Available Rooms:\n";
        for (const auto& room : rooms) {
            if (!room.isBooked) {
                cout << "Room " << room.roomNumber << "\n";
            }
        }
    }

    bool bookRoom(const string& guestName) {
        displayAvailableRooms();

        int roomNumber;
        cout << "Enter the room number you want to book: ";
        cin >> roomNumber;

        for (auto& room : rooms) {
            if (room.roomNumber == roomNumber && !room.isBooked) {
                room.isBooked = true;
                bookings.push_back(Booking(nextBookingId++, roomNumber, guestName));
                cout << "Room booked successfully.\n";
                return true;
            }
        }

        cout << "Invalid room number or the room is already booked.\n";
        return false;
    }

    void displayBookings() const {
        cout << "Current Bookings:\n";
        for (const auto& booking : bookings) {
            cout << "Booking ID: " << booking.bookingId << ", Room Number: " << booking.roomNumber
                 << ", Guest Name: " << booking.guestName << "\n";
        }
    }

    void checkOut(int bookingId) {
        auto it = find_if(bookings.begin(), bookings.end(), [bookingId](const Booking& booking) {
            return booking.bookingId == bookingId;
        });

        if (it != bookings.end()) {
            it->roomNumber;
            for (auto& room : rooms) {
                if (room.roomNumber == it->roomNumber) {
                    room.isBooked = false;
                    cout << "Check-out successful.\n";
                    bookings.erase(it);
                    return;
                }
            }
        }

        cout << "Invalid booking ID or check-out failed.\n";
    }

    void registerComplaint(const string& guestName, const string& complaint) {
        string fullComplaint = "Guest: " + guestName + "\nComplaint: " + complaint;
        complaints.push_back(fullComplaint);
        cout << "Complaint registered successfully.\n";
    }

    void viewComplaints() const {
        if (complaints.empty()) {
            cout << "No complaints registered.\n";
        } else {
            cout << "Current Complaints:\n";
            for (const auto& complaint : complaints) {
                cout << complaint << "\n-----------------------\n";
            }
        }
    }

    void displayMenu() const {
        cout << "Menu:\n";
        for (const auto& item : menu) {
            cout << item.name << "\tRs." << item.price << endl;
        }
    }

    MenuItem getItemByName(const string& itemName) const {
        // Convert itemName to lowercase for case-insensitive comparison
        string lowercaseItemName = itemName;
        transform(lowercaseItemName.begin(), lowercaseItemName.end(), lowercaseItemName.begin(), ::tolower);

        for (const auto& item : menu) {
            // Convert item name to lowercase for case-insensitive comparison
            string lowercaseItem = item.name;
            transform(lowercaseItem.begin(), lowercaseItem.end(), lowercaseItem.begin(), ::tolower);

            if (lowercaseItem == lowercaseItemName) {
                return item;
            }
        }
        return MenuItem("", 0.0);
    }

private:
    vector<MenuItem> menu = {
        {"Burger", 49},
        {"Pizza", 139},
        {"Pasta", 69},
        {"Maggi", 49},
        {"French Fries", 60},
        {"Potato Chilli", 80},
        {"Paneer Chilli", 99},
        {"Fried Rice", 70},
        {"Spring Roll", 50},
        {"Soft Drink", 50},
        {"Mineral Water", 25},
    };
};

int getUserChoice() {
    cout << "Enter your choice: ";
    string input;
    cin >> input;

    try {
        return stoi(input);
    } catch (const invalid_argument& e) {
        throw invalid_argument("Invalid response. Please enter a valid integer.");
    }
}

int main() {
    Hotel hotel(10); // Create a hotel with 10 rooms
    RoomService roomService;

    while (true) {
        try {
            cout << "\nHotel Management System:\n";
            cout << "1. Display Available Rooms\n";
            cout << "2. Book a Room\n";
            cout << "3. Display Current Bookings\n";
            cout << "4. Check-out\n";
            cout << "5. Register Complaint\n";
            cout << "6. View Complaints\n";
            cout << "7. Display Menu\n";
            cout << "8. Place Order\n";
            cout << "9. View Orders\n";
            cout << "10. Exit\n";

            int choice = getUserChoice();

            switch (choice) {
                case 1:
                    hotel.displayAvailableRooms();
                    break;

                case 2: {
                    string guestName;
                    cout << "Enter your name: ";
                    cin >> guestName;
                    hotel.bookRoom(guestName);
                    break;
                }

                case 3:
                    hotel.displayBookings();
                    break;

                case 4: {
                    int bookingId;
                    cout << "Enter the booking ID for check-out: ";
                    cin >> bookingId;
                    hotel.checkOut(bookingId);
                    break;
                }

                case 5: {
                    string guestName, complaint;
                    cout << "Enter your name: ";
                    cin >> guestName;
                    cin.ignore(); // Ignore newline character left in the buffer
                    cout << "Enter your complaint: ";
                    getline(cin, complaint);
                    hotel.registerComplaint(guestName, complaint);
                    break;
                }

                case 6:
                    hotel.viewComplaints();
                    break;

                case 7:
                    hotel.displayMenu();
                    break;

                case 8: {
                    Order order;
                    cout << "Enter item name to add to the order (or 'done' to finish): ";
                    cin.ignore(); // Ignore newline character left in the buffer
                    string itemName;
                    while(getline(cin, itemName) && itemName!="done"){
                        MenuItem item = hotel.getItemByName(itemName);
                        if (item.name.empty()) {
                            cout << "Invalid item. Please enter a valid item name.\n";
                        } else {
                            order.addItem(item);
                        }
                    } // Read a line with spaces
                    
                    roomService.placeOrder(order);
                    break;
                }

                case 9:
                    roomService.viewOrders();
                    break;

                case 10:
                    cout << "Exiting program. Goodbye!\n";
                    return 0;

                default:
                    cout << "Invalid choice. Please enter a valid option.\n";
            }
        } catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }

    return 0;
}