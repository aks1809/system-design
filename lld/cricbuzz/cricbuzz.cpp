#include <bits/stdc++.h>

using namespace std;

enum MATCH_TYPE{
    T20,
    ONE_DAY,
    TEST
};

enum MATCH_STATUS{
    YET_TO_START,
    ONGOING,
    ENDED,
    DEAD
};

enum PLAYER_STATE{
    OUT,
    PLAYING,
    YET_TO_PLAY
};

enum BALL_TYPE{
    DOT,
    WIDE,
    NO_BALL,
    BALL,
    WICKET
};

enum PLAYER_TYPE{
    CAPTAIN,
    BOWLER,
    BATSMAN,
    WICKET_KEEPER
};

class MatchType{
    private:
        MATCH_TYPE matchType;
        int overs;
    public:
        MatchType(){}
        MatchType(MATCH_TYPE matchType, int overs){
            this->matchType=matchType;
            this->overs=overs;
        }
};

class Ball{
    private:
        BALL_TYPE ball_type;
        int runs;
    public:
        Ball(){}
        Ball(BALL_TYPE ball_type, int runs){
            this->ball_type=ball_type;
            this->runs=runs;
        }
        void displayBallInfo(){
            cout<<"Ball Info: "<<ball_type<<", "<<runs<<"\n";
        }
        BALL_TYPE getBallType(){
            return this->ball_type;
        }
        int getRuns(){
            return this->runs;
        }
};

class Over{
    private:
        int valid_ball_count;
        vector<Ball*> balls;
    public:
        Over(){
            valid_ball_count=0;
        }
        int getValidBallCount(){
            return this->valid_ball_count;
        }
        void updateBallCount(int ball_count) {
            this->valid_ball_count+=ball_count;
        }
        void insertBall(Ball* ball){
            this->balls.push_back(ball);
        }
};

class BattingScoreCard{
    private:
        int runs, balls_faced;
        float strike_rate;
    public:
        BattingScoreCard(){
            this->runs=0;
            this->balls_faced=0;
            this->strike_rate=0;
        }
        void viewScoreCard(){
            cout<<this->runs<<", "<<this->balls_faced<<", "<<this->strike_rate<<"\n";
        }
        void addBall(int runs, int balls_faced){
            this->runs+=runs;
            this->balls_faced+=balls_faced;
        }
};

class BowllingScoreCard{
    private:
        int balls, runs;
        float economy;
    public:
        BowllingScoreCard(){
            this->runs=0;
            this->balls=0;
            this->economy=0;
        }
        int getBallsBowled(){
            return this->balls;
        }
        void viewScoreCard(){
            cout<<"Score card: "<<this->balls<<", "<<this->runs<<", "<<this->economy<<"\n";
        }
        void addBall(int runs, int balls){
            this->balls+=balls;
            this->runs+=runs;
        }
};

class Player{
    private:
        int id;
        string name;
        PLAYER_STATE state;
        PLAYER_TYPE type;
    public:
        BattingScoreCard *battingScoreCard;
        BowllingScoreCard *bowllingScroreCard;
        Player(int id,string name,PLAYER_STATE state, PLAYER_TYPE type){
            this->id=id;
            this->name=name;
            this->state=state;
            this->type=type;
            this->battingScoreCard=new BattingScoreCard();
            this->bowllingScroreCard=new BowllingScoreCard();
        }
        int getId(){
            return this->id;
        }
        void viewPlayerDetails(){
            cout<<"Player Details: "<<this->id<<", "<<this->name<<"\n";
        }
        void viewPlayerBattingScoreCard(){
            cout<<"Score Card of: "<<this->name<<", "<<this->state<<"\n";
            this->battingScoreCard->viewScoreCard();
        }
        void viewPlayerBowllingScoreCard(){
            cout<<"Score Card of: "<<this->name<<", "<<this->state<<"\n";
            this->bowllingScroreCard->viewScoreCard();
        }
        void updatePlayerState(PLAYER_STATE state){
            this->state=state;
        }
};

class BattingController{
    private:
        Player *striker, *nonStriker;
        vector<Player*> playerList;
        int next_player_index;
    public:
        BattingController(vector<Player*> playerList){
            this->striker=nullptr;
            this->nonStriker=nullptr;
            this->next_player_index=0;
            this->playerList=playerList;
        }
        Player* getCurrentStriker(){
            if(!striker) {
                if(next_player_index==playerList.size()) return nullptr;
                striker = playerList[next_player_index++];
            }
            if(!nonStriker) {
                if(next_player_index==playerList.size()) return nullptr;
                nonStriker = playerList[next_player_index++];
            }
            return striker;
        }
        void markOut(Player *player){
            if(striker->getId() == player->getId()){
                striker=nullptr;
            }else{
                nonStriker=nullptr;
            }
        }
        void handleBat(Ball *ball){
            if(ball->getBallType()==BALL){
                striker->battingScoreCard->addBall(ball->getRuns(), 1);
                if(ball->getRuns()%2!=0){
                    swap(striker, nonStriker);
                }
            }else if(ball->getBallType()==WICKET){
                this->striker->updatePlayerState(OUT);
                this->striker=nullptr;
            }
        }
};

class BowllingController{
    private:
        Player *currentBowler;
        unordered_set<Player *> remaining_bowlers;
    public:
        BowllingController(vector<Player*> playerList){
            this->currentBowler=nullptr;
            for(auto i:playerList){
                remaining_bowlers.insert(i);
            }
        }
        Player* getCurrentBowler(){
            if(!currentBowler){
                currentBowler=*remaining_bowlers.begin();
                remaining_bowlers.erase(currentBowler);
                
            }else if(currentBowler->bowllingScroreCard->getBallsBowled()/6>0 && currentBowler->bowllingScroreCard->getBallsBowled()%6==0){
                // time to switch bowler
                Player *newBowler = *remaining_bowlers.begin();
                remaining_bowlers.erase(newBowler);
                currentBowler=newBowler;
                if(currentBowler->bowllingScroreCard->getBallsBowled()<30){
                    remaining_bowlers.insert(currentBowler);
                }
            }
            return currentBowler;
        }
        void handleBall(Ball *ball){
            if(ball->getBallType()!=NO_BALL && ball->getBallType()!=WIDE){
                currentBowler->bowllingScroreCard->addBall(ball->getRuns(), 1);
            }else{
                currentBowler->bowllingScroreCard->addBall(ball->getRuns(), 0);
            }
        }
};

class Team{
    private:
        int id;
        string name;
        vector<Player*> players;
        BattingController *battingController;
        BowllingController *bowllingController;
    public:
        Team(){}
        Team(int id, string name, vector<Player*> players){
            this->id=id;
            this->name=name;
            this->players=players;
            this->battingController=new BattingController(players);
            this->bowllingController=new BowllingController(players);
        }
        void displayTeamsDetails(){
            cout<<"Team Details: "<<id<<", "<<name<<"\n";
        }
        BattingController* getBattingController(){
            return this->battingController;
        }
        BowllingController* getBowllingController(){
            return this->bowllingController;
        }
        void viewBattingScoreCard(){
            for(auto i:players){
                i->viewPlayerBattingScoreCard();
            }
        }
        void viewBowllingScoreCard(){
            for(auto i:players){
                i->viewPlayerBowllingScoreCard();
            }
        }
};

class Inning{
    private:
        Team *battingTeam, *bowllingTeam;
        vector<Over*> overs;
    public:
        Inning(){}
        Inning(Team *battingTeam, Team *bowllingTeam){
            this->battingTeam=battingTeam;
            this->bowllingTeam=bowllingTeam;
        }
        void addBall(Ball *ball){
            if(this->overs.size()>0 && overs.back()->getValidBallCount()<6){
                if(ball->getBallType()!=DOT){
                    overs.back()->updateBallCount(1);
                }
            }else{
                overs.push_back(new Over());
                if(ball->getBallType()!=DOT){
                    overs.back()->updateBallCount(1);
                }
            }
            overs.back()->insertBall(ball);
        }
};

class Match{
    private:
        int id;
        MatchType *matchType;
        Team *tossWinner;
        MATCH_STATUS matchStatus;
        Team *winner;
        int datetime;
        string venue;
        int currentInning;
        vector<Team*> teams;
        vector<Inning*> innings;
    public:
        Match(int id,MatchType *matchType,MATCH_STATUS matchStatus,int datetime,string venue,vector<Team*> teams){
            this->id=id;
            this->matchType=matchType;
            this->matchStatus=matchStatus;
            this->datetime=datetime;
            this->venue=venue;
            this->teams=teams;
            this->currentInning=0;
        }
        Team* toss(){
            tossWinner = teams[0];
            return tossWinner;
        }
        void startMatch(){
            matchStatus = ONGOING;
            innings = { new Inning(teams[0], teams[1]), new Inning(teams[1], teams[0]) };
        }
        Team* getBowllingTeam(){
            if(currentInning==0) return teams[1];
            else return teams[0];
        }
        Team* getBattingTeam(){
            if(currentInning==0) return teams[0];
            else return teams[1];
        }
        Inning* getCurrentInning(){
            return this->innings[currentInning];
        }
};

class BallObserver{
    private:
        BattingController *battingController;
        BowllingController *bowllingController;
        Inning *inning;
    public:
        BallObserver(BattingController *battingController, BowllingController *bowllingController, Inning* inning){
            this->bowllingController = bowllingController;
            this->battingController = battingController;
            this->inning = inning;
        }
        void bowl(Ball *ball){
            // ball->displayBallInfo();
            bowllingController->getCurrentBowler()->viewPlayerDetails();
            cout<<"- to -";
            battingController->getCurrentStriker()->viewPlayerDetails();
            battingController->handleBat(ball);
            bowllingController->handleBall(ball);
            inning->addBall(ball);
            battingController->getCurrentStriker()->viewPlayerBattingScoreCard();
        }
};

int main() {
    // team India
    Player *viratKohli = new Player(rand(), "Virat Kohli", YET_TO_PLAY, BATSMAN);
    Player *rohitSharma = new Player(rand(), "Rohit Sharma", YET_TO_PLAY, CAPTAIN);
    Player *subhmanGill = new Player(rand(), "Subhman Gill", YET_TO_PLAY, BATSMAN);
    Player *jaspritBumhra = new Player(rand(), "Jasprit Bumhra", YET_TO_PLAY, BOWLER);
    Player *kLRahul = new Player(rand(), "KL Rahul", YET_TO_PLAY, WICKET_KEEPER);
    vector<Player*> indianPlayers = {viratKohli, rohitSharma, subhmanGill, jaspritBumhra, kLRahul};

    // team Pakistan
    Player *mohdA = new Player(rand(), "Mohd. A", YET_TO_PLAY, CAPTAIN);
    Player *mohdB = new Player(rand(), "Mohd. B", YET_TO_PLAY, BATSMAN);
    Player *mohdC = new Player(rand(), "Mohd. C", YET_TO_PLAY, BATSMAN);
    Player *mohdD = new Player(rand(), "Mohd. D", YET_TO_PLAY, WICKET_KEEPER);
    Player *mohdE = new Player(rand(), "Mohd. E", YET_TO_PLAY, BOWLER);
    vector<Player*> pakistaniPlayers = {mohdA, mohdB, mohdC, mohdD, mohdE};

    Team *teamIndia = new Team(rand(), "Team India", indianPlayers);
    Team *teamPakistan = new Team(rand(), "Team Pakistan", pakistaniPlayers);

    MatchType *matchType = new MatchType(T20, 20);
    Match *match = new Match(rand(), matchType, YET_TO_START, 121314, "Chinnaswamy", {teamIndia, teamPakistan});

    Team *tossWinner = match->toss();
    cout<<"Team batting right now\n";
    tossWinner->displayTeamsDetails();

    match->startMatch();

    Ball *ball = new Ball(BALL, 1);
    Ball *outBall = new Ball(WICKET, 0);
    BallObserver *ballObserver = new BallObserver(match->getBattingTeam()->getBattingController(), match->getBowllingTeam()->getBowllingController(), match->getCurrentInning());

    ballObserver->bowl(ball);
    ballObserver->bowl(ball);
    ballObserver->bowl(ball);
    ballObserver->bowl(ball);
    ballObserver->bowl(outBall);
    ballObserver->bowl(ball);
    ballObserver->bowl(ball);
    ballObserver->bowl(ball);
    ballObserver->bowl(ball);

    /*
        YET TO IMPLEMENT
            1. Completion of innings
            2. Match winner
            3. Strike rotate on over end
    */
    return 0;
}