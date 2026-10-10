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
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] != ' ')
        {
            x = x + s[i];
        }
    }
    if(x.length() < 6 || x.length() > 9)
        return false;
    if(!isalpha(x[0]) || !isalpha(x[1]))
        return false;
    if(!isdigit(x[2]))
        return false;
    if(!isalpha(x[3]) || !isalpha(x[4]))
        return false;
    int lastNumberLength = x.length() - 5;
    if(lastNumberLength < 1 || lastNumberLength > 4)
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
bool duplicateBusNumber(string busNo)
{
    for(int i = 0; i < normalCount; i++)
    {
        if(normalBuses[i].getBusNo() == busNo)
            return true;
    }
    for(int i = 0; i < deluxeCount; i++)
    {
        if(deluxeBuses[i].getBusNo() == busNo)
            return true;
    }
    return false;
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
    cout<<"\n \t\t\t\t\t\t\t\t\tNORMAL BUSES \n";
    if(normalCount == 0)
    {
        cout<<"\t\t\t\t\t\t\t\tNo Normal Bus available.\n";
    }
    else
    {
        for(int i = 0; i < normalCount; i++)
        {
            cout<<"\n\t\t\t\t\t\t\t\tBus No       : "<<normalBuses[i].getBusNo();
            cout<<"\n\t\t\t\t\t\t\t\tRoute        : "<<normalBuses[i].getRoute();
            cout<<"\n\t\t\t\t\t\t\t\tDistance     : "<<normalBuses[i].getDistance() << " KM\n";
        }
    }
    cout<<"\n \t\t\t\t\t\t\t\t\tDELUXE BUSES \n";
    if(deluxeCount == 0)
    {
        cout<<"\t\t\t\t\t\t\t\tNo Deluxe Bus available.\n";
    }
    else
    {
        for(int i = 0; i < deluxeCount; i++)
        {
            cout<<"\n\t\t\t\t\t\t\t\tBus No   : "<<deluxeBuses[i].getBusNo();
            cout<<"\n\t\t\t\t\t\t\t\tRoute    : "<<deluxeBuses[i].getRoute();
            cout<<"\n\t\t\t\t\t\t\t\tDistance : "<<deluxeBuses[i].getDistance()<<" KM\n";
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
        cout<<"\t\t\t\t\t\t\t\t\tADD BUS"<<endl<<endl;
        cout<<"\t\t\t\t\t\t\t\t1. Normal Bus"<<endl;
        cout<<"\t\t\t\t\t\t\t\t2. Deluxe Bus"<<endl;
        cout<<"\t\t\t\t\t\t\t\t3. Exit"<<endl<<endl;
        cout<<"\t\t\t\t\t\t\t\tEnter your Choice : ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"\t\t\t\t\t\t\t\tInvalid choice! Please enter a number.\n";
            system("pause");
            continue;
        }
        switch(choice)
        {
            case 1:
                if(normalCount >= Max_Bus)
                {
                    cout<<"\n\t\t\t\t\t\t\t\tNormal Bus limit reached!\n";
                    system("pause");
                    return;
                }
                normalBuses[normalCount].inputBus();
                normalCount++;
                saveData();
                cout<<"\n\t\t\t\t\t\t\t\tNormal Bus added successfully!\n";
                system("pause");
                break;
            case 2:
                if(deluxeCount >= Max_Bus)
                {
                    cout<<"\n\t\t\t\t\t\t\t\tDeluxe Bus limit reached!\n";
                    system("pause");
                    return;
                }
                deluxeBuses[deluxeCount].inputBus();
                deluxeCount++;
                saveData();
                cout<<"\n\t\t\t\t\t\t\t\tDeluxe Bus added successfully!\n";
                system("pause");
                break ;
            case 3:
                return;
            default:
                cout<<endl<<"\t\t\t\t\t\t\t\tInvalid Choice! Please Try Again"<<endl;
                system("pause");
                continue;
        }
    }
}
void Bus :: inputBus()
{
    while(true)
    {
        cout<<"\t\t\t\t\t\t\t\tEnter Bus Number: ";
        cin>>ws;
        getline(cin, busNo);
        if(!validBusNumber(busNo))
        {
            cout<<"\t\t\t\t\t\t\t\tInvalid Bus Number! Please Enter like a Ba1Pa1234 or Ba 1 Pa 1234.\n";
            continue;
        }
        if(duplicateBusNumber(busNo))
        {
            cout<<"\t\t\t\t\t\t\t\tBus Number already exists! Please enter a different Bus Number.\n";
            continue;
        }
        break;
    }
    while(true)
    {
        cout<<"\t\t\t\t\t\t\t\tEnter Route: ";
        getline(cin, route);
        if(validRoute(route))
        {
            break;
        }
        cout<<"\t\t\t\t\t\t\t\tInvalid Route! Only letters, spaces and - are allowed.\n";
    }
    while(true)
    {
        cout<<"\t\t\t\t\t\t\t\tEnter Distance (KM): ";
        if(cin>>distanceKm && distanceKm > 0 && distanceKm <=5000)
        {
            break;
        }
        cout<<"\t\t\t\t\t\t\t\tInvalid distance! Please enter a value between 1 and 5000 KM.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}
void Bus :: showSeatMap()
{
    system("cls");
    cout<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tBUS SEAT MAP\n\n";
    cout<<"\t\t\t\t\t\t\t\t    LEFT SIDE          RIGHT SIDE\n\n";
    for(int i = 0; i < Seats; i += 4)
    {
        cout<<"\t\t\t\t\t\t\t\t";
        if(seatBooked[i])
            cout<<"[XX] ";
        else
            cout<<"[" << setw(2) << setfill('0') << i + 1 << "] ";
        cout<<"\t";
        if(seatBooked[i + 1])
            cout<<"[XX] ";
        else
            cout<<"[" << setw(2) << setfill('0') << i + 2 << "] ";
        cout<<"\t\t";
        if(seatBooked[i + 2])
            cout<<"[" << "XX" << "] ";
        else
            cout<<"[" << setw(2) << setfill('0') << i + 3 << "] ";
        cout<<"\t";
        if(seatBooked[i + 3])
            cout<<"[" << "XX" << "] ";
        else
            cout<<"[" << setw(2) << setfill('0') << i + 4 << "] ";
        cout<<endl;
        setfill(' ');
    }
    cout<<"\n\t\t\t\t\t\t\t\tXX = Booked\n";
    cout<<"\t\t\t\t\t\t\t\tNumber = Available\n";
    system("pause");
}
void Bus :: viewseat_map()
{
    while(true)
    {
        system("cls");
        if(normalCount == 0 && deluxeCount == 0)
        {
            cout<<"\n\t\t\t\t\t\t\t\tNo buses available!\n";
            system("pause");
            return;
        }
        int choice;
        cout<<"\n\t\t\t\t\t\t\t\tVIEW SEAT MAP \n\n";
        cout<<"\t\t\t\t\t\t\t\t1. Normal Bus\n";
        cout<<"\t\t\t\t\t\t\t\t2. Deluxe Bus\n";
        cout<<"\t\t\t\t\t\t\t\t3. Back\n\n";
        cout<<"\t\t\t\t\t\t\t\tEnter your choice: ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"\t\t\t\t\t\t\t\tInvalid input! Please enter a number.\n";
            system("pause");
            return;
        }
        if(choice == 1)
        {
            if(normalCount == 0)
            {
                cout<<"\n\t\t\t\t\t\t\t\tNo Normal Bus available!\n";
                system("pause");
                return;
            }
            cout<<"\n\t\t\t\t\t\t\t\tAvailable Normal Buses:\n";
            for(int i = 0; i < normalCount; i++)
            {
                cout<<"\t\t\t\t\t\t\t\t"<<i + 1 << ". "<< normalBuses[i].getBusNo()<< " - "<< normalBuses[i].getRoute()<< endl;
            }
            int busChoice;
            cout<<"\n\t\t\t\t\t\t\t\tSelect Bus: ";
            if(!(cin >> busChoice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"\t\t\t\t\t\t\t\tInvalid input! Please enter a number.\n";
                system("pause");
                continue;
            }
            if(busChoice < 1 || busChoice > normalCount)
            {
                cout<<"\t\t\t\t\t\t\t\tInvalid bus choice!\n";
                system("pause");
                continue;
            }
            normalBuses[busChoice - 1].showSeatMap();
        }
        else if(choice == 2)
        {
            if(deluxeCount == 0)
            {
                cout<<"\n\t\t\t\t\t\t\t\tNo Deluxe Bus available!\n";
                system("pause");
                return;
            }
            cout<<"\n\t\t\t\t\t\t\t\tAvailable Deluxe Buses:\n";
            for(int i = 0; i < deluxeCount; i++)
            {
                cout<<"\t\t\t\t\t\t\t\t"<<i + 1 << ". "<< deluxeBuses[i].getBusNo()<< " - "<< deluxeBuses[i].getRoute()<< endl;
            }
            int busChoice;
            cout<<"\n\t\t\t\t\t\t\t\tSelect Bus: ";
            if(!(cin >> busChoice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"\t\t\t\t\t\t\t\tInvalid input! Please enter a number.\n";
                system("pause");
                continue;
            }
            if(busChoice < 1 || busChoice > deluxeCount)
            {
                cout<<"\t\t\t\t\t\t\t\tInvalid bus choice!\n";
                system("pause");
                continue;
            }
            deluxeBuses[busChoice - 1].showSeatMap();
        }
        else if(choice == 3)
        {
            return;
        }
        else
        {
            cout<<"\n\t\t\t\t\t\t\t\tInvalid choice!\n";
            system("pause");
            continue;
        }
    }
}
bool Bus :: bookSeat(int seat, string name)
{
    if(seat < 1 || seat > Seats)
    {
        cout<<"\n\t\t\t\t\t\t\t\tInvalid seat number!\n";
        cout<<"\n\t\t\t\t\t\t\t\tSeat number must be between 1 and 40.";
        return false;
    }
    if(seatBooked[seat - 1])
    {
        throw SeatAlreadyBookedException("\t\t\t\t\t\t\t\t""Seat " + to_string(seat) + " is already booked!");
    }
    seatBooked[seat - 1] = true;
    passenger[seat - 1] = name;
    return true;
}
void Bus :: cancelSeat(int seat)
{
    if(seat < 1 || seat > Seats)
    {
        cout<<"\n\t\t\t\t\t\t\t\tInvalid seat number!\n";
        return;
    }
    if(!seatBooked[seat - 1])
    {
        cout<<"\n\t\t\t\t\t\t\t\tThis seat is not booked!\n";
        return;
    }
    seatBooked[seat - 1] = false;
    passenger[seat - 1] = "";
    cout<<"\n\t\t\t\t\t\t\t\tSeat "<<seat<<" has been cancelled successfully!\n";
}
void Bus :: cancelTicket()
{
    while(true)
    {
        system("cls");
        if(ticketCount == 0)
        {
            cout<<"\n\t\t\t\t\t\t\t\tNo tickets available to cancel!\n";
            system("pause");
            return;
        }
        int ticketNo;
        cout<<"\n\t\t\t\t\t\t\t\tCANCEL TICKET \n\n";
        cout<<"\t\t\t\t\t\t\t\tEnter Ticket Number: ";
        if(!(cin >> ticketNo))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"\t\t\t\t\t\t\t\tInvalid input! Please enter a number.\n";
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
            cout<<"\n\t\t\t\t\t\t\t\tTicket not found!\n";
            system("pause");
            continue;
        }
        cout<<"\n\t\t\t\t\t\t\t\t\tTICKET DETAILS"<<endl<<endl;
        cout<<"\t\t\t\t\t\t\t\tTicket No.     : " << tickets[ticketIndex].getTicketNo() << endl;
        cout<<"\t\t\t\t\t\t\t\tBus No.        : " << tickets[ticketIndex].getBusNo() << endl;
        cout<<"\t\t\t\t\t\t\t\tSeat No.       : " << tickets[ticketIndex].getSeatNo() << endl;
        cout<<"\t\t\t\t\t\t\t\tPassenger Name : " << tickets[ticketIndex].getPassengerName() << endl;
        cout<<"\t\t\t\t\t\t\t\tFare           : Rs. " << fixed << setprecision(2) << tickets[ticketIndex].getFare() << endl;
        char confirm;
        cout<<"\n\t\t\t\t\t\t\tAre you sure you want to cancel this ticket? (Y/N): ";
        cin>>confirm;
        if(confirm == 'N' || confirm == 'n')
        {
            cout<<"\n\t\t\t\t\t\t\t\tTicket cancellation cancelled.\n";
            system("pause");
            return;
        }
        if(confirm != 'Y' && confirm != 'y')
        {
            cout<<"\n\t\t\t\t\t\t\t\tInvalid choice! Please enter Y or N.\n";
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
            cout<<"\n\t\t\t\t\t\t\t\tBus associated with this ticket was not found!\n";
            system("pause");
            continue;
        }
        for(int i = ticketIndex; i < ticketCount - 1; i++)
        {
            tickets[i] = tickets[i + 1];
        }
        ticketCount--;
        saveData();
        cout<<"\n\t\t\t\t\t\t\t\tTicket "<<ticketNo<<" cancelled successfully!\n";
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
            cout<<"\n\t\t\t\t\t\t\t\tNo tickets available!\n";
            system("pause");
            return;
        }
        int choice;
        cout<<"\n\t\t\t\t\t\t\t\tSEARCH TICKET \n";
        cout<<"\t\t\t\t\t\t\t\t1. Search by Ticket Number\n";
        cout<<"\t\t\t\t\t\t\t\t2. Search by Passenger Name\n";
        cout<<"\t\t\t\t\t\t\t\t3. Back\n";
        cout<<"\n\t\t\t\t\t\t\t\tEnter your choice: ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"\t\t\t\t\t\t\t\tInvalid input!\n";
            system("pause");
            continue;
        }
        if(choice == 1)
        {
            int ticketNo;
            cout<<"\n\t\t\t\t\t\t\t\tEnter Ticket Number: ";
            if(!(cin >> ticketNo))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"\t\t\t\t\t\t\t\tInvalid ticket number!\n";
                system("pause");
                continue;
            }
            bool found = false;
            for(int i = 0; i < ticketCount; i++)
            {
                if(tickets[i].getTicketNo() == ticketNo)
                {
                    cout<<"\n\t\t\t\t\t\t\t\tTICKET DETAILS \n\n";
                    cout<<"\t\t\t\t\t\t\t\tTicket Number   : "<<tickets[i].getTicketNo()<<endl;
                    cout<<"\t\t\t\t\t\t\t\tBus Number      : "<<tickets[i].getBusNo()<<endl;
                    cout<<"\t\t\t\t\t\t\t\tSeat Number     : "<<tickets[i].getSeatNo()<<endl;
                    cout<<"\t\t\t\t\t\t\t\tPassenger Name  : "<<tickets[i].getPassengerName()<<endl;
                    cout<<"\t\t\t\t\t\t\t\tFare            : Rs. "<<fixed<<setprecision(2)<<tickets[i].getFare()<<endl;
                    found = true;
                    break;
                }
            }
            if(!found)
                cout<<"\n\t\t\t\t\t\t\t\tTicket not found!\n";

            system("pause");
        }
        else if(choice == 2)
        {
            cin.ignore(1000, '\n');
            string name;
            while(true)
            {
                cout<<"\n\t\t\t\t\t\t\t\tEnter Passenger Name: ";
                getline(cin, name);
                if(validName(name))
                {
                    break;
                }
                cout<<"\t\t\t\t\t\t\t\tInvalid name! Only letters and spaces are allowed.\n";
            }
            bool found = false;
            cout<<"\n\t\t\t\t\t\t\t\tSEARCH RESULTS \n";
            for(int i = 0; i < ticketCount; i++)
            {
                if(tickets[i].getPassengerName() == name)
                {
                    cout<<"\n\t\t\t\t\t\t\t\tTicket Number   : "<<tickets[i].getTicketNo();
                    cout<<"\n\t\t\t\t\t\t\t\tBus Number      : "<<tickets[i].getBusNo();
                    cout<<"\n\t\t\t\t\t\t\t\tSeat Number     : "<<tickets[i].getSeatNo();
                    cout<<"\n\t\t\t\t\t\t\t\tPassenger Name  : "<<tickets[i].getPassengerName();
                    cout<<"\n\t\t\t\t\t\t\t\tFare            : Rs. "<<fixed<<setprecision(2)<<tickets[i].getFare()<<endl;
                    found = true;
                }
            }
            if(!found)
                cout<<"\n\t\t\t\t\t\t\t\tNo ticket found for this passenger name.\n";

            system("pause");
        }
        else if(choice == 3)
        {
            return;
        }
        else
        {
            cout<<"\n\t\t\t\t\t\t\t\tInvalid choice!\n";
            system("pause");
        }
    }
}
void Bus :: saveData()
{
    ofstream file("D:\\LOQ\\bus.txt");
    if(!file)
    {
        cout<<"\n\t\t\t\t\t\t\t\tError opening file for saving!\n";
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
            file<<normalBuses[i].seatBooked[j] << endl;
            file<<normalBuses[i].passenger[j] << endl;
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
    cout<<"\n\t\t\t\t\t\t\t\tData saved successfully!\n";
}
void Bus :: loadData()
{
    ifstream file("D:\\LOQ\\bus.txt");
    if(!file)
    {
        return;
    }
    file>>normalCount;
    file>>deluxeCount;
    if(normalCount < 0 || normalCount > Max_Bus ||
       deluxeCount < 0 || deluxeCount > Max_Bus)
    {
        cout<<"\n\t\t\t\t\t\t\t\tInvalid bus data found in file!\n";
        normalCount = 0;
        deluxeCount = 0;
        ticketCount = 0;
        nextTicketNo = 1;
        file.close();
        return;
    }
    file.ignore(1000, '\n');
    for(int i = 0; i < normalCount; i++)
    {
        getline(file, normalBuses[i].busNo);
        getline(file, normalBuses[i].route);
        file>>normalBuses[i].distanceKm;
        file.ignore(1000, '\n');
        for(int j = 0; j < Seats; j++)
        {
            file>>normalBuses[i].seatBooked[j];
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
    if(ticketCount < 1 || ticketCount > Max_Tickets)
    {
        cout<<"\n\t\t\t\t\t\t\t\tInvalid ticket data found in file!\n";
        ticketCount = 0;
        nextTicketNo = 1;
        file.close();
        return;
    }
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
            cout<<"\n\t\t\t\t\t\t\t\tNo buses available!\n";
            system("pause");
            return;
        }
        int type;
        cout<<"\n\t\t\t\t\t\t\t\tBOOK TICKET \n";
        cout<<"\t\t\t\t\t\t\t\t1. Normal Bus\n";
        cout<<"\t\t\t\t\t\t\t\t2. Deluxe Bus\n";
        cout<<"\t\t\t\t\t\t\t\t3. Back\n";
        cout<<"\n\t\t\t\t\t\t\t\tEnter your choice: ";
        if(!(cin >> type))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"\t\t\t\t\t\t\t\tInvalid input! Please enter a number.\n";
            system("pause");
            return;
        }
        if(type == 1)
        {
            if(normalCount == 0)
            {
                cout<<"\n\t\t\t\t\t\t\t\tNo Normal Bus available!\n";
                system("pause");
                continue;
            }
            cout<<"\n\t\t\t\t\t\t\t\tAvailable Normal Buses:\n";
            for(int i = 0; i < normalCount; i++)
            {
                cout<<"\t\t\t\t\t\t\t\t"<<i + 1 << ". "<< normalBuses[i].getBusNo()<< " - "<< normalBuses[i].getRoute()<< endl;
            }
            int busChoice;
            cout<<"\n\t\t\t\t\t\t\t\tSelect Bus: ";
            if(!(cin >> busChoice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"\t\t\t\t\t\t\t\tInvalid input! Please enter a number.\n";
                system("pause");
                return;
            }
            if(busChoice < 1 || busChoice > normalCount)
            {
                cout<<"\t\t\t\t\t\t\t\tInvalid bus choice!\n";
                system("pause");
                return;
            }
            Bus &selectedBus = normalBuses[busChoice - 1];
            selectedBus.showSeatMap();
            int seat;
            while(true)
            {
                cout<<"\n\t\t\t\t\t\t\t\tEnter Seat Number (1-40): ";
                if(cin>>seat && seat >= 1 && seat <= 40)
                {
                    break;
                }
                cout<<"\t\t\t\t\t\t\t\tInvalid seat number! Please enter a number between 1 and 40.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
            string name;
            while(true)
            {
                cout<<"\t\t\t\t\t\t\t\tEnter Passenger Name: ";
                getline(cin, name);
                if(validName(name))
                {
                    break;
                }
                cout<<"\t\t\t\t\t\t\t\tInvalid passenger name! Only letters and spaces are allowed.\n";
            }
            if(ticketCount >= Max_Tickets)
            {
                cout<<"\n\t\t\t\t\t\t\t\tTicket limit reached! Cannot book more tickets.\n";
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
                cout<<"\n\t\t\t\t\t\t\t\tTicket Number : "<<nextTicketNo<<endl;
                cout<<"\t\t\t\t\t\t\t\tBus Number    : "<<selectedBus.getBusNo()<<endl;
                cout<<"\t\t\t\t\t\t\t\tSeat Number   : "<<seat<<endl;
                cout<<"\t\t\t\t\t\t\t\tPassenger     : "<<name<<endl;
                cout<<"\t\t\t\t\t\t\t\tFare          : "<<fare<<endl;
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
                cout<<"\n\t\t\t\t\t\t\t\tNo Deluxe Bus available!\n";
                system("pause");
                continue;
            }
            cout<<"\n\t\t\t\t\t\t\t\tAvailable Deluxe Buses:\n";
            for(int i = 0; i < deluxeCount; i++)
            {
                cout<<"\t\t\t\t\t\t\t\t"<< i + 1 << ". "<< deluxeBuses[i].getBusNo()<< " - "<< deluxeBuses[i].getRoute()<< endl;
            }
            int busChoice;
            cout<<"\n\t\t\t\t\t\t\t\tSelect Bus: ";
            if(!(cin >> busChoice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"\t\t\t\t\t\t\t\tInvalid input! Please enter a number.\n";
                system("pause");
                return;
            }
            if(busChoice < 1 || busChoice > deluxeCount)
            {
                cout<<"\t\t\t\t\t\t\t\tInvalid bus choice!\n";
                system("pause");
                return;
            }
            Bus &selectedBus = deluxeBuses[busChoice - 1];
            selectedBus.showSeatMap();
            int seat;
            while(true)
            {
                cout<<"\n\t\t\t\t\t\t\t\tEnter Seat Number (1-40): ";
                if(cin>>seat && seat >= 1 && seat <= 40)
                {
                    break;
                }
                cout<<"\t\t\t\t\t\t\t\tInvalid seat number! Please enter a number between 1 and 40.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
            string name;
            while(true)
            {
                cout<<"\t\t\t\t\t\t\t\tEnter Passenger Name: ";
                getline(cin, name);
                if(validName(name))
                {
                    break;
                }
                cout<<"\t\t\t\t\t\t\t\tInvalid passenger name! Only letters and spaces are allowed.\n";
            }
            if(ticketCount >= Max_Tickets)
            {
                cout<<"\n\t\t\t\t\t\t\t\tTicket limit reached! Cannot book more tickets.\n";
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
                cout<<"\n\t\t\t\t\t\t\t\tTicket Number : "<<nextTicketNo<<endl;
                cout<<"\t\t\t\t\t\t\t\tBus Number    : "<<selectedBus.getBusNo()<<endl;
                cout<<"\t\t\t\t\t\t\t\tSeat Number   : "<<seat<<endl;
                cout<<"\t\t\t\t\t\t\t\tPassenger     : "<<name<<endl;
                cout<<"\t\t\t\t\t\t\t\tFare          : "<<fare<<endl;
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
            cout<<"\n\t\t\t\t\t\t\t\tInvalid choice!\n";
        }
        system("pause");
        continue;
    }
}
bool validUsername(string s)
{
    if(s.empty()) return false;
    for(char c:s)
        if(!isalpha(c))
            return false;
    return true;
}
bool validPassword(string s)
{
    return s.length() >= 4;
}
void signup()
{
    string u,p;
    while(true)
    {
        system("cls");
        cout<<"\n\t\t\t\t\t\t\t\t\tSIGNUP \n";
        cout<<"\t\t\t\t\t\t\t\tUsername: ";
        cin>>u;
        if(validUsername(u))
            break;
        cout<<"\t\t\t\t\t\t\t\tInvalid username! Letters only.\n";
    }
    while(true)
    {
        cout<<"\t\t\t\t\t\t\t\tPassword: ";
        cin>>p;
        if(validPassword(p))
            break;

        cout<<"\t\t\t\t\t\t\t\tPassword must be at least 4 characters!\n";
    }
    ofstream f("D:\\LOQ\\login.txt",ios::app);
    f<<u<<endl<<p<<endl;
    f.close();
    cout<<"\t\t\t\t\t\t\t\tAccount created successfully!\n";
    system("pause");
}
bool login()
{
    string u,p,su,sp;
    ifstream f("D:\\LOQ\\login.txt");
    if(!f)
    {
        cout<<"\n\t\t\t\t\t\t\t\tNo account found! Please Sign Up First.\n";
        system("pause");
        return false;
    }
    system("cls");
    cout<<"\n\t\t\t\t\t\t\t\t\tLOGIN \n";
    cout<<"\n\t\t\t\t\t\t\t\tUsername: ";
    cin>>u;
    cout<<"\t\t\t\t\t\t\t\tPassword: ";
    cin>>p;
    while(getline(f,su))
    {
        getline(f,sp);
        if(u==su && p==sp)
        {
            cout<<"\n\t\t\t\t\t\t\t\tLogin successful!\n";
            return true;
        }
    }
    cout<<"\n\t\t\t\t\t\t\t\tInvalid username or password!\n";
    system("pause");
    return false;
}
void accountMenu()
{
    while(true)
    {
        system("cls");
        cout<<"\n\t\t\t\t\t\t\t\tLOGIN FOR TICKET RESERVATION\n\n";
        cout<<"\t\t\t\t\t\t\t\t1. Sign Up\n";
        cout<<"\t\t\t\t\t\t\t\t2. Login\n";
        cout<<"\t\t\t\t\t\t\t\t3. Exit\n";
        cout<<"\n\t\t\t\t\t\t\t\tEnter choice: ";
        int choice;
        if(!(cin>>choice))
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"\t\t\t\t\t\t\t\tInvalid input! Enter a number.\n";
            system("pause");
            continue;
        }
        switch(choice)
        {
            case 1:
                signup();
                break;
            case 2:
                if(login())
                    return;
                break;
            case 3:
                exit(0);
            default:
                cout<<"\t\t\t\t\t\t\t\tInvalid choice! Choose 1-3.\n";
                system("pause");
        }
    }
}
void Bus ::menu()
{
    p:
    system("cls");
    int choice;
    cout<<"\t\t\t\t\t\t\t\t\tMain Menu"<<endl<<endl;
    cout<<"\t\t\t\t\t\t\t\t1. Add Bus"<<endl;
    cout<<"\t\t\t\t\t\t\t\t2. List Buses"<<endl;
    cout<<"\t\t\t\t\t\t\t\t3. View Seat Map"<<endl;
    cout<<"\t\t\t\t\t\t\t\t4. Book ticket"<<endl;
    cout<<"\t\t\t\t\t\t\t\t5. Cancel Ticket"<<endl;
    cout<<"\t\t\t\t\t\t\t\t6. Search Ticket"<<endl;
    cout<<"\t\t\t\t\t\t\t\t7. Save & Exit"<<endl;
    cout<<"\n\t\t\t\t\t\t\t\tEnter Your choice: ";
    if(!(cin >> choice))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"\t\t\t\t\t\t\t\tInvalid choice! Please enter a number.\n";
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
            system("pause");
            return;
        default:
            cout<<endl<<"\t\t\t\t\t\t\t\tInvalid Choice! Please Try Again"<<endl;
            system("pause");
    }
    goto p;
}
int main()
{
    NormalBus b;
    b.loadData();
    while(true)
    {
        accountMenu();
        b.menu();
    }
    return 0;
}