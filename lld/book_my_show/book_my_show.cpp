#include<bits/stdc++.h>

using namespace std;

enum SEAT_TYPE{
    SILVER,
    GOLD,
    PLATINUM
};

enum LANGUAGE{
    HINDI,
    ENGLISH,
    KANNADA
};

enum PAYMENT_STATUS{
    BOOKED,
    PENDING,
    FAILED
};

class Address{
    private:
        string address, city;
    public:
        Address(){}
        Address(string address, string city){
            this->address = address;
            this->city = city;
        }
        string getAddress() const {
            return this->address + " " + this->city;
        }
        string getCity() const {
            return this->city;
        }
};

class User{
    private:
        int id;
        string name, phone_number, password;
    public:
        Address address;
        User() {}
        User(int id, string name, string phone_number, string password, string address, string city){
            this->id = id;
            this->name = name;
            this->phone_number = phone_number;
            this->password = password;
            this->address = Address(address, city);
        }
        int getId() const {
            return this->id;
        }
};

class Movie{
    private:
        int id, duration;
        string name;
        vector<LANGUAGE> languages;
    public:
        Movie() {}
        Movie(int id, int duration, string name, vector<LANGUAGE> languages){
            this->id = id;
            this->duration = duration;
            this->name = name;
            this->languages = languages;
        }
        int getMovieId(){
            return this->id;
        }
        void viewMovieDetails(){
            cout<<"Movie Details: "<<this->id<<", "<<this->name<<", "<<this->duration<<", ";
            for(auto i:this->languages){
                cout<<i<<", ";
            }
            cout<<"\n";
        }
};

class MovieController{
    private:
        unordered_map<string, vector<Movie>> city_to_movie;
        vector<Movie> movies;
    public:
        void addMovie(string city, Movie movie) {
            movies.push_back(movie);
            city_to_movie[city].push_back(movie);
        }
        void viewMoviesInACity(string city){
            for(auto i:city_to_movie[city]){
                i.viewMovieDetails();
            }
        }
};

class Seat{
    private:
        int id;
        SEAT_TYPE type_of_seat;
        float price;
    public:
        Seat(int id, SEAT_TYPE type_of_seat, float price){
            this->id = id;
            this->type_of_seat = type_of_seat;
            this->price = price;
        }
        float getSeatPrice(){
            return this->price;
        }
        int getId(){
            return this->id;
        }
};

class Screen{
    private:
        int id;
    public:
        vector<Seat> list_of_seats;
        Screen() {}
        Screen(int id){
            this->id = id;
            this->list_of_seats.push_back(Seat(rand(), SILVER, 50));
            this->list_of_seats.push_back(Seat(rand(), SILVER, 50));
            this->list_of_seats.push_back(Seat(rand(), GOLD, 100));
            this->list_of_seats.push_back(Seat(rand(), GOLD, 100));
            this->list_of_seats.push_back(Seat(rand(), PLATINUM, 200));
            this->list_of_seats.push_back(Seat(rand(), PLATINUM, 200));
        }
};

class Theatre{
    private:
        int id;
        string name;
    public:
        Address address;
        vector<Screen> screens;
        Theatre() {}
        Theatre(int id, string name, string address, string city){
            this->id=id;
            this->name=name;
            this->address=Address(address, city);
            this->screens.push_back(Screen(1));
            this->screens.push_back(Screen(2));
        }
        void addScreens(Screen screen){
            screens.push_back(screen);
        }
        void viewTheatreDetails(){
            cout<<"Theatre Details: "<<this->id<<", "<<this->name<<", "<<this->address.getAddress()<<"\n";
        }
};

class TheatreController{
    private:
        unordered_map<string, vector<Theatre>> city_to_theatre;
        vector<Theatre> theatres;
    public:
        void addTheatre(Theatre theatre) {
            theatres.push_back(theatre);
            city_to_theatre[theatre.address.getCity()].push_back(theatre);
        }
        void viewTheatresInACity(string city){
            for(auto i:city_to_theatre[city]){
                i.viewTheatreDetails();
            }
        }
};

class Show{
    private:
        int id;
        int start_time;
        LANGUAGE language;
        Screen screen;
        vector<Seat> bookedSeats;
    public:
        Movie movie;
        Theatre theatre;
        Show() {}
        Show(int id, int start_time, LANGUAGE language, Movie movie, Theatre theatre, Screen screen){
            this->id = id;
            this->start_time = start_time;
            this->language = language;
            this->theatre = theatre;
            this->movie = movie;
            this->screen = screen;
        }
        void viewShowDetails(){
            cout<<"Show Details: "<<this->id<<", "<<this->start_time<<", "<<this->language<<"\n";
        }
        int getShowID(){
            return this->id;
        }
        void viewSeatDetails(){
            for(auto i:screen.list_of_seats){
                for(auto j:bookedSeats){
                    if(i.getId()==j.getId()){
                        cout<<i.getId()<<", "<<i.getSeatPrice()<<", Booked\n";
                        return;    
                    }
                }
                cout<<i.getId()<<", "<<i.getSeatPrice()<<", Available\n";
            }
        }
        Seat* getSelectedSeat(int id){
            for(auto &i:screen.list_of_seats){
                if(i.getId()==id) return &i;
            }
            return nullptr;
        }
        bool getSeatAvailability(Seat seat){
            for(auto i:bookedSeats){
                if(i.getId()==seat.getId()) return false;
            }
            return true;
        }
        void markSeatBooked(Seat seat){
            bookedSeats.push_back(seat);
        }
};

class Payment{
    private:
        int id;
        PAYMENT_STATUS status;
        string mode;
    public:
        Payment() {}
        Payment(int id, PAYMENT_STATUS status, string mode){
            this->id;
            this->status=status;
            this->mode=mode;
        }
        bool makePayment(PAYMENT_STATUS status) {
            this->status = status;
            return true;
        }
        PAYMENT_STATUS getPaymentStatus(){
            return this->status;
        }
};

class Booking{
    private:
        int id;
        User user;
        Show* show;
        Payment payment;
    public:
        Booking(int id, User user, Show* show){
            this->id=id;
            this->user=user;
            this->show=show;
            this->payment = Payment(rand(), PENDING, "UPI");
        }
        Payment getPayment(){
            return this->payment;
        }
        PAYMENT_STATUS getPaymentStatus(){
            return this->payment.getPaymentStatus();
        }
};

class ShowController{
    private:
        vector<Show *> shows;
    public:
        void addShows(Show *show) {
            shows.push_back(show);
        }
        void viewShows(int movieId, string city){
            for(auto i:shows){
                if(i->movie.getMovieId()==movieId && i->theatre.address.getCity()==city){
                    i->theatre.viewTheatreDetails();
                    i->viewShowDetails();
                    cout<<"---------------------------------------------\n";
                }
            }
        }
        Show* getShowByID(int id){
            for(auto &i:shows){
                if(i->getShowID()==id) return i;
            }
            return nullptr;
        }
        Booking* bookShowSeat(Show *selectedShow, Seat selectedSeat, User user){
            bool seatStatus = selectedShow->getSeatAvailability(selectedSeat);
            if(!seatStatus){
                return nullptr;
            }
            Booking *booking = new Booking(rand(), user, selectedShow);
            selectedShow->markSeatBooked(selectedSeat);
            return booking;
        }
};

int main(){
    const string usersCity = "Bangalore";
    User* user = new User(1, "Akshay Chaturvedi", "8057466860", "1234567890", "HSR Layout", usersCity);
    TheatreController *theatreController = new TheatreController();
    MovieController *movieController = new MovieController();
    ShowController *showController = new ShowController();
    // add theatres
    Theatre theatre1 = Theatre(1, "Nexus", "Kormangla", "Bangalore");
    Theatre theatre2 = Theatre(2, "Cinepolis", "HSR Layout", "Bangalore");
    Theatre theatre3 = Theatre(3, "PVR", "Laxmi Nagar", "Delhi");
    theatreController->addTheatre(theatre1);
    theatreController->addTheatre(theatre2);
    theatreController->addTheatre(theatre3);

    // add movies
    Movie animal = Movie(1, 100, "Animal", {ENGLISH, HINDI, KANNADA});
    Movie bahubali = Movie(2, 100, "Bahubali", {HINDI});
    movieController->addMovie("Bangalore", animal);
    movieController->addMovie("Delhi", animal);
    movieController->addMovie("Bangalore", bahubali);

    // addShows
    Show *show1 = new Show(1, 1200, HINDI, animal, theatre1, theatre1.screens[0]);
    Show *show2 = new Show(2, 1200, ENGLISH, animal, theatre1, theatre1.screens[1]);
    Show *show3 = new Show(3, 1800, HINDI, animal, theatre2, theatre2.screens[0]);
    Show *show4 = new Show(4, 1800, KANNADA, animal, theatre2, theatre2.screens[1]);
    Show *show5 = new Show(5, 1800, HINDI, animal, theatre3, theatre3.screens[0]);
    Show *show6 = new Show(6, 1820, HINDI, animal, theatre3, theatre3.screens[1]);

    Show *show7 = new Show(7, 1500, HINDI, bahubali, theatre1, theatre1.screens[0]);
    Show *show8 = new Show(8, 1500, HINDI, bahubali, theatre3, theatre3.screens[0]);

    showController->addShows(show1);
    showController->addShows(show2);
    showController->addShows(show3);
    showController->addShows(show4);
    showController->addShows(show5);
    showController->addShows(show6);
    showController->addShows(show7);
    showController->addShows(show8);

    // theatreController->viewTheatresInACity(usersCity);
    // movieController->viewMoviesInACity(usersCity);

    // view theatres showing a moview and all the shows in those theatres
    const int selectedMovieId = 1;
    // showController->viewShows(selectedMovieId, usersCity);

    // select seats from seat view
    const int selectedShowId = 3;
    Show *selectedShow = showController->getShowByID(selectedShowId);
    // selectedShow->getSeatDetails();

    const int selectedSeatId = 783368690;
    Seat *selectedSeat = selectedShow->getSelectedSeat(selectedSeatId);
    Booking *booking = showController->bookShowSeat(selectedShow, *selectedSeat, *user);
    if(!booking){
        cout<<"Selected seat not available, Try another\n";
    }else{
        cout<<"Seat locked make payment now\n";
        Payment payment = booking->getPayment();
        payment.makePayment(BOOKED);
        cout<<"Here is the payment status: "<<booking->getPaymentStatus()<<"\n";
    }

    cout<<"-------------------------------------------------\n";
    
    booking = showController->bookShowSeat(selectedShow, *selectedSeat, *user);
    if(!booking){
        cout<<"Selected seat not available, Try another\n";
    }else{
        cout<<"Seat locked make payment now\n";
        Payment payment = booking->getPayment();
        payment.makePayment(BOOKED);
        cout<<"Here is the payment status: "<<booking->getPaymentStatus()<<"\n";
    }

    return 0;
}