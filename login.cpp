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
        cout<<"\n SIGNUP \n";
        cout<<"Username: ";
        cin>>u;
        if(validUsername(u))
            break;
        cout<<"Invalid username! Letters only.\n";
    }
    while(true)
    {
        cout<<"Password: ";
        cin>>p;
        if(validPassword(p))
            break;

        cout<<"Password must be at least 4 characters!\n";
    }
    ofstream f("D:\\LOQ\\login.txt",ios::app);
    f<<u<<endl<<p<<endl;
    f.close();
    cout<<"Account created successfully!\n";
    system("pause");
}
bool login()
{
    string u,p,su,sp;
    ifstream f("D:\\LOQ\\login.txt");
    if(!f)
    {
        cout<<"\nNo account found! Please Sign Up First.\n";
        system("pause");
        return false;
    }
    system("cls");
    cout<<"\n LOGIN \n";
    cout<<"Username: ";
    cin>>u;
    cout<<"Password: ";
    cin>>p;
    while(getline(f,su))
    {
        getline(f,sp);
        if(u==su && p==sp)
        {
            cout<<"\nLogin successful!\n";
            return true;
        }
    }
    cout<<"\nInvalid username or password!\n";
    system("pause");
    return false;
}
void accountMenu()
{
    while(true)
    {
        system("cls");
        cout<<"\n LOGIN FOR TICKET RESERVATION \n";
        cout<<"1. Sign Up\n";
        cout<<"2. Login\n";
        cout<<"3. Exit\n";
        cout<<"Enter choice: ";
        int choice;
        if(!(cin>>choice))
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Invalid input! Enter a number.\n";
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
                cout<<"Invalid choice! Choose 1-3.\n";
                system("pause");
        }
    }
}