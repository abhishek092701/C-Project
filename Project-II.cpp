#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<cctype>

using namespace std;

const int Seats = 40;
const int Max_Bus = 10;
const int Max_Tickets = 400;

class SeatAlreadyBookedException
{
private:
    string message;
public:
    SeatAlreadyBookedException(string msg)
    {
        message = msg;
    }
    string getMessage() const
    {
        return message;
    }
};
class Ticket
{
private:
    int ticketNo;
    string busNo;
    int seatNo;
    string passengerName;
    double fare;

public:
    Ticket()
    {
        ticketNo = 0;
        busNo = "";
        seatNo = 0;
        passengerName = "";
        fare = 0;
    }
    Ticket(int t, string b, int s, string p, double f)
    {
        ticketNo = t;
        busNo = b;
        seatNo = s;
        passengerName = p;
        fare = f;
    }
    int getTicketNo()
    {
        return ticketNo;
    }
    string getBusNo()
    {
        return busNo;
    }
    int getSeatNo()
    {
        return seatNo;
    }
    string getPassengerName()
    {
        return passengerName;
    }
    double getFare()
    {
        return fare;
    }
};
class Bus{
    protected:
        string busNo;
        string route;
        double distanceKm;
        bool seatBooked[Seats];
        string passenger[Seats];
    public:
        Bus();
        void menu();
        void add_bus();
        void inputBus();
        virtual double farePerSeat() = 0;
        void list_buses();
        void showSeatMap();
        void viewseat_map();
        bool bookSeat(int seat, string name);
        void cancelSeat(int seat);
        void cancelTicket();
        void searchTicket();
        void bookTicket();
        void saveData();
        void loadData();
        string getBusNo()
        {
            return busNo;
        }
        string getRoute()
        {
            return route;
        }
        double getDistance()
        {
            return distanceKm;
        }

};
class NormalBus : public Bus
{
    private:
        double rate;
    public:
        NormalBus()
        {
            rate = 2.0;
        }
        double farePerSeat()
        {
            return distanceKm * rate;
        }
};
class DeluxeBus : public Bus
{
    private:
        double rate;
        double acCharge;
    public:
        DeluxeBus()
        {
            rate = 3.0;
            acCharge = 100;
        }
        double farePerSeat()
        {
            return (distanceKm * rate) + acCharge;
        }
};
NormalBus normalBuses[Max_Bus];
DeluxeBus deluxeBuses[Max_Bus];
int normalCount = 0;
int deluxeCount = 0;
Ticket tickets[Max_Tickets];
int ticketCount = 0;
int nextTicketNo = 1;
Bus :: Bus()
{
    busNo = "";
    route = "";
    distanceKm = 0;
    for(int i = 0; i < Seats; i++)
    {
        seatBooked[i] = false;
        passenger[i] = "";
    }
}
bool validName(string name)
{
    if(name.empty())
        return false;
    bool hasLetter = false;
    for(int i = 0; i < name.length(); i++)
    {
        if(isalpha(name[i]))
        {
            hasLetter = true;
        }
        else if(name[i] != ' ')
        {
            return false;
        }
    }
    return hasLetter;
}
bool validBusNumber(string s)
{
    string x = "";
    for(char c : s)
        if(c != ' ')
            x += c;
    if(x.length() < 6 || x.length() > 9)
        return false;
    if(!isalpha(x[0]) || !isalpha(x[1]) || !isdigit(x[2]) || !isalpha(x[3]) || !isalpha(x[4]))
        return false;
    for(int i = 5; i < x.length(); i++)
    {
        if(!isdigit(x[i]))
            return false;
    }
    bool allZero = true;
    for(int i = 5; i < x.length(); i++)
    {
        if(x[i] != '0')
        {
            allZero = false;
            break;
        }
    }
    if(allZero)
        return false;
    return true;
}
bool validRoute(string s)
{
    int d=0;
    bool letter=false;
    for(char c:s)
    {
        if(isalpha(c))
            letter=true;
        else if(c=='-')
            d++;
        else if(c!=' ')
            return false;
    }
    return d==1 && letter && s.front()!='-' && s.back()!='-';
}
void Bus :: list_buses()
{
    system("cls");
    cout<<"\n NORMAL BUSES \n";
    if(normalCount == 0)
    {
        cout<<"No Normal Bus available.\n";
    }
    else
    {
        for(int i = 0; i < normalCount; i++)
        {
            cout<<"\nBus No       : "<<normalBuses[i].getBusNo();
            cout<<"\nRoute        : "<<normalBuses[i].getRoute();
            cout<<"\nDistance     : "<<normalBuses[i].getDistance() << " KM";
            cout<<"\n";
        }
    }
    cout<<"\n DELUXE BUSES \n";
    if(deluxeCount == 0)
    {
        cout << "No Deluxe Bus available.\n";
    }
    else
    {
        for(int i = 0; i < deluxeCount; i++)
        {
            cout<<"\nBus No       : "<<deluxeBuses[i].getBusNo();
            cout<<"\nRoute        : "<<deluxeBuses[i].getRoute();
            cout<<"\nDistance     : "<<deluxeBuses[i].getDistance()<<" KM";
            cout<<"\n";
        }
    }
    system("pause");
}
void Bus :: add_bus()
{
    while(true)
    {
        system("cls");
        int choice;
        cout<<"ADD BUS"<<endl;
        cout<<"1. Normal Bus"<<endl;
        cout<<"2. Deluxe Bus"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter your Choice : ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Invalid choice! Please enter a number.\n";
            system("pause");
            return;
        }
        switch(choice)
        {
            case 1:
                if(normalCount >= Max_Bus)
                {
                    cout<<"\nNormal Bus limit reached!\n";
                    system("pause");
                    return;
                }
                normalBuses[normalCount].inputBus();
                normalCount++;
                saveData();
                cout<<"\nNormal Bus added successfully!\n";
                system("pause");
                break;
            case 2:
                if(deluxeCount >= Max_Bus)
                {
                    cout<<"\nDeluxe Bus limit reached!\n";
                    system("pause");
                    return;
                }
                deluxeBuses[deluxeCount].inputBus();
                deluxeCount++;
                saveData();
                cout<<"\nDeluxe Bus added successfully!\n";
                system("pause");
                break ;
            case 3:
                return;
            default:
                cout<<endl<<"Invalid Choice! Please Try Again"<<endl;
                system("pause");
                continue;
        }
    }
}
void Bus :: inputBus()
{
    while(true)
    {
        cout<<"Enter Bus Number: ";
        cin>>ws;
        getline(cin, busNo);
        if(validBusNumber(busNo))
        {
            break;
        }
        cout<<"Invalid Bus Number!\n";
    }
    while(true)
    {
        cout<<"Enter Route: ";
        getline(cin, route);
        if(validRoute(route))
        {
            break;
        }
        cout<<"Invalid Route! Only letters, spaces and - are allowed.\n";
    }
    while(true)
    {
        cout<<"Enter Distance (KM): ";
        if(cin >> distanceKm && distanceKm > 0)
        {
            break;
        }
        cout<<"Invalid distance! Please enter a value between 1 and 5000 KM.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}
void Bus :: showSeatMap()
{
    system("cls");
    cout<<endl;
    cout<<"            BUS SEAT MAP\n";
    cout<<"       LEFT SIDE          RIGHT SIDE\n\n";
    for(int i = 0; i < Seats; i += 4)
    {
        if(seatBooked[i])
            cout<<"   [XX] ";
        else
            cout<<"   [" << setw(2) << setfill('0') << i + 1 << "] ";
        if(seatBooked[i + 1])
            cout<<"[XX] ";
        else
            cout<<"[" << setw(2) << setfill('0') << i + 2 << "] ";
        cout << "      ";
        if(seatBooked[i + 2])
            cout<<"[" << "XX" << "] ";
        else
            cout<<"[" << setw(2) << setfill('0') << i + 3 << "] ";
        if(seatBooked[i + 3])
            cout << "[" << "XX" << "] ";
        else
            cout<<"[" << setw(2) << setfill('0') << i + 4 << "] ";
        cout<<endl;
        setfill(' ');
    }
    cout<<"XX = Booked\n";
    cout<<"Number = Available\n";
    system("pause");
}
void Bus :: viewseat_map()
{
    while(true)
    {
        system("cls");
        if(normalCount == 0 && deluxeCount == 0)
        {
            cout<<"\nNo buses available!\n";
            system("pause");
            return;
        }
        int choice;
        cout<<"\n VIEW SEAT MAP \n";
        cout<<"1. Normal Bus\n";
        cout<<"2. Deluxe Bus\n";
        cout<<"3. Back\n";
        cout<<"Enter your choice: ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Invalid input! Please enter a number.\n";
            system("pause");
            return;
        }
        if(choice == 1)
        {
            if(normalCount == 0)
            {
                cout<<"\nNo Normal Bus available!\n";
                system("pause");
                return;
            }
            cout<<"\nAvailable Normal Buses:\n";
            for(int i = 0; i < normalCount; i++)
            {
                cout<<i + 1 << ". "<< normalBuses[i].getBusNo()<< " - "<< normalBuses[i].getRoute()<< endl;
            }
            int busChoice;
            cout<<"\nSelect Bus: ";
            if(!(cin >> busChoice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Invalid input! Please enter a number.\n";
                system("pause");
                return;
            }
            if(busChoice < 1 || busChoice > normalCount)
            {
                cout<<"Invalid bus choice!\n";
                system("pause");
                return;
            }
            normalBuses[busChoice - 1].showSeatMap();
        }
        else if(choice == 2)
        {
            if(deluxeCount == 0)
            {
                cout<<"\nNo Deluxe Bus available!\n";
                system("pause");
                return;
            }
            cout<<"\nAvailable Deluxe Buses:\n";
            for(int i = 0; i < deluxeCount; i++)
            {
                cout<<i + 1 << ". "<< deluxeBuses[i].getBusNo()<< " - "<< deluxeBuses[i].getRoute()<< endl;
            }
            int busChoice;
            cout<<"\nSelect Bus: ";
            if(!(cin >> busChoice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Invalid input! Please enter a number.\n";
                system("pause");
                return;
            }
            if(busChoice < 1 || busChoice > deluxeCount)
            {
                cout<<"Invalid bus choice!\n";
                system("pause");
                return;
            }
            deluxeBuses[busChoice - 1].showSeatMap();
        }
        else if(choice == 3)
        {
            return;
        }
        else
        {
            cout<<"\nInvalid choice!\n";
            system("pause");
            continue;
        }
    }
}
bool Bus :: bookSeat(int seat, string name)
{
    if(seat < 1 || seat > Seats)
    {
        cout<<"\nInvalid seat number!\n";
        cout<<"\nSeat number must be between 1 and 40.";
        return false;
    }
    if(seatBooked[seat - 1])
    {
        throw SeatAlreadyBookedException("Seat " + to_string(seat) + " is already booked!");
    }
    seatBooked[seat - 1] = true;
    passenger[seat - 1] = name;
    return true;
}
void Bus :: cancelSeat(int seat)
{
    if(seat < 1 || seat > Seats)
    {
        cout<<"\nInvalid seat number!\n";
        return;
    }
    if(!seatBooked[seat - 1])
    {
        cout<<"\nThis seat is not booked!\n";
        return;
    }
    seatBooked[seat - 1] = false;
    passenger[seat - 1] = "";
    cout<<"\nSeat "<<seat<<" has been cancelled successfully!\n";
}
void Bus :: cancelTicket()
{
    while(true)
    {
        system("cls");
        if(ticketCount == 0)
        {
            cout<<"\nNo tickets available to cancel!\n";
            system("pause");
            return;
        }
        int ticketNo;
        cout<<"\nCANCEL TICKET \n";
        cout<<"Enter Ticket Number: ";
        if(!(cin >> ticketNo))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Invalid input! Please enter a number.\n";
            system("pause");
            continue;
        }
        int ticketIndex = -1;
        for(int i = 0; i < ticketCount; i++)
        {
            if(tickets[i].getTicketNo() == ticketNo)
            {
                ticketIndex = i;
                break;
            }
        }
        if(ticketIndex == -1)
        {
            cout<<"\nTicket not found!\n";
            system("pause");
            continue;
        }
        char confirm;
        cout<<"\nAre you sure you want to cancel this ticket? (Y/N): ";
        cin >> confirm;
        if(confirm == 'N' || confirm == 'n')
        {
            cout<<"\nTicket cancellation cancelled.\n";
            system("pause");
            return;
        }
        if(confirm != 'Y' && confirm != 'y')
        {
            cout<<"\nInvalid choice! Please enter Y or N.\n";
            system("pause");
            continue;
        }
        string busNo = tickets[ticketIndex].getBusNo();
        int seatNo = tickets[ticketIndex].getSeatNo();
        bool seatCancelled = false;
        for(int i = 0; i < normalCount; i++)
        {
            if(normalBuses[i].getBusNo() == busNo)
            {
                normalBuses[i].cancelSeat(seatNo);
                seatCancelled = true;
                break;
            }
        }
        if(!seatCancelled)
        {
            for(int i = 0; i < deluxeCount; i++)
            {
                if(deluxeBuses[i].getBusNo() == busNo)
                {
                    deluxeBuses[i].cancelSeat(seatNo);
                    seatCancelled = true;
                    break;
                }
            }
        }
        if(!seatCancelled)
        {
            cout<<"\nBus associated with this ticket was not found!\n";
            system("pause");
            continue;
        }
        for(int i = ticketIndex; i < ticketCount - 1; i++)
        {
            tickets[i] = tickets[i + 1];
        }
        ticketCount--;
        saveData();
        cout<<"\nTicket "<<ticketNo<<" cancelled successfully!\n";
        system("pause");
        return;
    }
}
void Bus :: searchTicket()
{
    while(true)
    {
        system("cls");
        if(ticketCount == 0)
        {
            cout<<"\nNo tickets available!\n";
            system("pause");
            return;
        }
        int choice;
        cout<<"\n SEARCH TICKET \n";
        cout<<"1. Search by Ticket Number\n";
        cout<<"2. Search by Passenger Name\n";
        cout<<"3. Back\n";
        cout<<"Enter your choice: ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Invalid input!\n";
            system("pause");
            continue;
        }
        if(choice == 1)
        {
            int ticketNo;
            cout<<"\nEnter Ticket Number: ";
            if(!(cin >> ticketNo))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Invalid ticket number!\n";
                system("pause");
                continue;
            }
            bool found = false;
            for(int i = 0; i < ticketCount; i++)
            {
                if(tickets[i].getTicketNo() == ticketNo)
                {
                    cout<<"\n TICKET DETAILS \n";
                    cout<<"Ticket Number   : "<<tickets[i].getTicketNo()<<endl;
                    cout<<"Bus Number      : "<<tickets[i].getBusNo()<<endl;
                    cout<<"Seat Number     : "<<tickets[i].getSeatNo()<<endl;
                    cout<<"Passenger Name  : "<<tickets[i].getPassengerName()<<endl;
                    cout<<"Fare            : Rs. "<<fixed<<setprecision(2)<<tickets[i].getFare()<<endl;
                    found = true;
                    break;
                }
            }
            if(!found)
                cout<<"\nTicket not found!\n";

            system("pause");
        }
        else if(choice == 2)
        {
            cin.ignore(1000, '\n');
            string name;
            while(true)
            {
                cout<<"\nEnter Passenger Name: ";
                getline(cin, name);
                if(validName(name))
                {
                    break;
                }
                cout<<"Invalid name! Only letters and spaces are allowed.\n";
            }
            bool found = false;
            cout<<"\n SEARCH RESULTS \n";
            for(int i = 0; i < ticketCount; i++)
            {
                if(tickets[i].getPassengerName() == name)
                {
                    cout<<"\nTicket Number   : "<<tickets[i].getTicketNo();
                    cout<<"\nBus Number      : "<<tickets[i].getBusNo();
                    cout<<"\nSeat Number     : "<<tickets[i].getSeatNo();
                    cout<<"\nPassenger Name  : "<<tickets[i].getPassengerName();
                    cout<<"\nFare            : Rs. "<<fixed<<setprecision(2)<<tickets[i].getFare()<<endl;
                    found = true;
                }
            }
            if(!found)
                cout<<"\nNo ticket found for this passenger name.\n";

            system("pause");
        }
        else if(choice == 3)
        {
            return;
        }
        else
        {
            cout<<"\nInvalid choice!\n";
            system("pause");
        }
    }
}
void Bus :: saveData()
{
    ofstream file("D:\\LOQ\\bus_data.txt");
    if(!file)
    {
        cout<<"\nError opening file for saving!\n";
        return;
    }
    file<<normalCount << endl;
    file<<deluxeCount << endl;
    for(int i = 0; i < normalCount; i++)
    {
        file<<normalBuses[i].busNo << endl;
        file<<normalBuses[i].route << endl;
        file<<normalBuses[i].distanceKm << endl;
        for(int j = 0; j < Seats; j++)
        {
            file << normalBuses[i].seatBooked[j] << endl;
            file << normalBuses[i].passenger[j] << endl;
        }
    }
    for(int i = 0; i < deluxeCount; i++)
    {
        file<<deluxeBuses[i].busNo << endl;
        file<<deluxeBuses[i].route << endl;
        file<<deluxeBuses[i].distanceKm << endl;
        for(int j = 0; j < Seats; j++)
        {
            file<<deluxeBuses[i].seatBooked[j] << endl;
            file<<deluxeBuses[i].passenger[j] << endl;
        }
    }
    file<<ticketCount << endl;
    file<<nextTicketNo << endl;
    for(int i = 0; i < ticketCount; i++)
    {
        file<<tickets[i].getTicketNo() << endl;
        file<<tickets[i].getBusNo() << endl;
        file<<tickets[i].getSeatNo() << endl;
        file<<tickets[i].getPassengerName() << endl;
        file<<tickets[i].getFare() << endl;
    }
    file.close();
    cout<<"\nData saved successfully!\n";
}
void Bus :: loadData()
{
    ifstream file("D:\\LOQ\\bus_data.txt");
    if(!file)
    {
        return;
    }
    file>>normalCount;
    file>>deluxeCount;
    file.ignore(1000, '\n');
    for(int i = 0; i < normalCount; i++)
    {
        getline(file, normalBuses[i].busNo);
        getline(file, normalBuses[i].route);
        file>>normalBuses[i].distanceKm;
        file.ignore(1000, '\n');
        for(int j = 0; j < Seats; j++)
        {
            file >> normalBuses[i].seatBooked[j];
            file.ignore(1000, '\n');
            getline(file, normalBuses[i].passenger[j]);
        }
    }
    for(int i = 0; i < deluxeCount; i++)
    {
        getline(file, deluxeBuses[i].busNo);
        getline(file, deluxeBuses[i].route);
        file>>deluxeBuses[i].distanceKm;
        file.ignore(1000, '\n');
        for(int j = 0; j < Seats; j++)
        {
            file >> deluxeBuses[i].seatBooked[j];
            file.ignore(1000, '\n');
            getline(file, deluxeBuses[i].passenger[j]);
        }
    }
    file>>ticketCount;
    file>>nextTicketNo;
    file.ignore(1000, '\n');
    for(int i = 0; i < ticketCount; i++)
    {
        int ticketNo;
        string busNo;
        int seatNo;
        string passengerName;
        double fare;
        file>>ticketNo;
        file.ignore(1000, '\n');
        getline(file, busNo);
        file>>seatNo;
        file.ignore(1000, '\n');
        getline(file, passengerName);
        file>>fare;
        file.ignore(1000, '\n');
        tickets[i] = Ticket(ticketNo,busNo,seatNo,passengerName,fare);
    }
    file.close();
}
void Bus :: bookTicket()
{
    while(true)
    {
        system("cls");
        if(normalCount == 0 && deluxeCount == 0)
        {
            cout<<"\nNo buses available!\n";
            system("pause");
            return;
        }
        int type;
        cout<<"\n========== BOOK TICKET ==========\n";
        cout<<"1. Normal Bus\n";
        cout<<"2. Deluxe Bus\n";
        cout<<"3. Back\n";
        cout<<"Enter your choice: ";
        if(!(cin >> type))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Invalid input! Please enter a number.\n";
            system("pause");
            return;
        }
        if(type == 1)
        {
            if(normalCount == 0)
            {
                cout<<"\nNo Normal Bus available!\n";
                system("pause");
                continue;
            }
            cout<<"\nAvailable Normal Buses:\n";
            for(int i = 0; i < normalCount; i++)
            {
                cout<<i + 1 << ". "<< normalBuses[i].getBusNo()<< " - "<< normalBuses[i].getRoute()<< endl;
            }
            int busChoice;
            cout<<"\nSelect Bus: ";
            if(!(cin >> busChoice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Invalid input! Please enter a number.\n";
                system("pause");
                return;
            }
            if(busChoice < 1 || busChoice > normalCount)
            {
                cout<<"Invalid bus choice!\n";
                system("pause");
                return;
            }
            Bus &selectedBus = normalBuses[busChoice - 1];
            selectedBus.showSeatMap();
            int seat;
            while(true)
            {
                cout<<"\nEnter Seat Number (1-40): ";
                if(cin>>seat && seat >= 1 && seat <= 40)
                {
                    break;
                }
                cout<<"Invalid seat number! Please enter a number between 1 and 40.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
            string name;
            while(true)
            {
                cout<<"Enter Passenger Name: ";
                getline(cin, name);
                if(validName(name))
                {
                    break;
                }
                cout<<"Invalid passenger name! Only letters and spaces are allowed.\n";
            }
            if(ticketCount >= Max_Tickets)
            {
                cout<<"\nTicket limit reached! Cannot book more tickets.\n";
                system("pause");
                return;
            }
            try
            {
                if(!selectedBus.bookSeat(seat, name))
                {
                    system("pause");
                    continue;
                }
                double fare = selectedBus.farePerSeat();
                tickets[ticketCount] = Ticket(nextTicketNo,selectedBus.getBusNo(),seat,name,fare);
                cout<<"\nTicket Number : "<<nextTicketNo<<endl;
                cout<<"Bus Number    : "<<selectedBus.getBusNo()<<endl;
                cout<<"Seat Number   : "<<seat<<endl;
                cout<<"Passenger     : "<<name<<endl;
                cout<<"Fare          : "<<fare<<endl;
                ticketCount++;
                nextTicketNo++;
                saveData();
            }
            catch(SeatAlreadyBookedException e)
            {
                cout<<e.getMessage()<<endl;
            }
        }
        else if(type == 2)
        {
            if(deluxeCount == 0)
            {
                cout<<"\nNo Deluxe Bus available!\n";
                system("pause");
                continue;
            }
            cout<<"\nAvailable Deluxe Buses:\n";
            for(int i = 0; i < deluxeCount; i++)
            {
                cout << i + 1 << ". "<< deluxeBuses[i].getBusNo()<< " - "<< deluxeBuses[i].getRoute()<< endl;
            }
            int busChoice;
            cout<<"\nSelect Bus: ";
            if(!(cin >> busChoice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Invalid input! Please enter a number.\n";
                system("pause");
                return;
            }
            if(busChoice < 1 || busChoice > deluxeCount)
            {
                cout<<"Invalid bus choice!\n";
                system("pause");
                return;
            }
            Bus &selectedBus = deluxeBuses[busChoice - 1];
            selectedBus.showSeatMap();
            int seat;
            while(true)
            {
                cout<<"\nEnter Seat Number (1-40): ";
                if(cin>>seat && seat >= 1 && seat <= 40)
                {
                    break;
                }
                cout<<"Invalid seat number! Please enter a number between 1 and 40.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
            string name;
            while(true)
            {
                cout<<"Enter Passenger Name: ";
                getline(cin, name);
                if(validName(name))
                {
                    break;
                }
                cout<<"Invalid passenger name! Only letters and spaces are allowed.\n";
            }
            if(ticketCount >= Max_Tickets)
            {
                cout<<"\nTicket limit reached! Cannot book more tickets.\n";
                system("pause");
                return;
            }
            try
            {
                if(!selectedBus.bookSeat(seat, name))
                {
                    system("pause");
                    continue;
                }
                double fare = selectedBus.farePerSeat();
                tickets[ticketCount] = Ticket(nextTicketNo,selectedBus.getBusNo(),seat,name,fare);
                cout<<"\nTicket Number : "<<nextTicketNo<<endl;
                cout<<"Bus Number    : "<<selectedBus.getBusNo()<<endl;
                cout<<"Seat Number   : "<<seat<<endl;
                cout<<"Passenger     : "<<name<<endl;
                cout<<"Fare          : "<<fare<<endl;
                ticketCount++;
                nextTicketNo++;
                saveData();
            }
            catch(SeatAlreadyBookedException e)
            {
                cout<<e.getMessage()<<endl;
            }
        }
        else if(type == 3)
        {
            return;
        }
        else
        {
            cout<<"\nInvalid choice!\n";
        }
        system("pause");
        continue;
    }
}
void Bus ::menu()
{
    p:
    system("cls");
    int choice;
    cout<<"Menu"<<endl;
    cout<<"1. Add Bus"<<endl;
    cout<<"2. List Buses"<<endl;
    cout<<"3. View Seat Map"<<endl;
    cout<<"4. Book ticket"<<endl;
    cout<<"5. Cancel Ticket"<<endl;
    cout<<"6. Search Ticket"<<endl;
    cout<<"7. Save & Exit"<<endl;
    cout<<"Enter Your choice: ";
    if(!(cin >> choice))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Invalid choice! Please enter a number.\n";
        system("pause");
        goto p;
    }
    switch(choice)
    {
        case 1:
            add_bus();
            break;
        case 2:
            list_buses();
            break;
        case 3:
            viewseat_map();
            break;
        case 4:
            bookTicket();
            break;
        case 5:
            cancelTicket();
            break;
        case 6:
            searchTicket();
            break;
        case 7:
            saveData();
            cout<<"\nExiting program...\n";
            exit(0);
        default:
            cout<<endl<<"Invalid Choice! Please Try Again"<<endl;
            system("pause");
    }
    goto p;
}
int main()
{
    NormalBus b;
    b.loadData();
    b.menu();
    return 0;
}