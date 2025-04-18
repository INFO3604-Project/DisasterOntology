/*
 This file contains the code for the module within the Veracity architecture that defines the compareText algorithm, as well as 
 the other features utilized in Veracity. We studied and reviewed this code to learn the inner workings of the algorithm's similarity
 score computation.
*/

/*
 * txc2.cc
 *
 *  Created on: 23 Feb 2021
 *      Author: neil_
 */

//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include <inet/routing/aodv/Aodv.h>
#include <string.h>
#include <omnetpp.h>
#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <fstream>
#include <chrono>
#include <vector>
#include <ctime>



using namespace inet;
using namespace aodv;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Txc2 : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    //virtual void *generateNewMessage();
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void receives();
    void credA(cMessage *msg);
    void credB(cMessage *msg);
    void credC(cMessage *msg);
    void update();
    char genFake();
    int genFavourites();
    int genListed();
    int genStatuses();
    int genFollowers();
    int genFriends();
    int genMessageRating();
    int genEyewitnessRating(std::string label);
    std::string genTimezone();
    std::string genLocation();
    std::string genSource();
    std::string genUserLanguage();
    std::string genLanguage();
    std::string genLabel();
    char genRandom();
    std::string genText();
    std::string genScreenName();
    char * genCreatedAt();
    int incrementVal(int nv);
    double credScore(int ratings[], double mRatings[], int numRatings, int numMessages, double Pc);
    float getMold(const std::vector<char>& vec);
    float getSimilarity(const std::vector<char>& lhs, const std::vector<char>& rhs);
    double compareText (std::string message, std::vector<std::string> keywords);
    double eyeRate(int eyeRating, double Pc);
    double eyeTruth(double eyeRatings[], int numEye);
    int i=0;
    double Pc=3.0;
    double Ec=0.0;
    int numRatings=0;
    int snumRatings=0;
    int numMessages=0;
    int ratings[1000];
    double mRatings[1000];
    int numEye=0;
    int numEyes=0;
    double eyeRatings[1000];
    std::ofstream myfile;
    std::ofstream myfiles;
    std::ofstream myfiless;
    int favourites_count = 0;
    int listed_count = 0;
    int statuses_count = 0;
    int followers_count = 0;
    int friends_count = 0;
    std::string screen_name;
    std::string language;
    std::string user_language;
    std::string timezone;
    std::string location;
    std::string label;
    char fake;
    double sMm =0;
    double sMsd =0;
    double eMm =0;
    double eMsd =0;
    std::vector<std::string> animals = {"Elephant", "Lion", "Deer", "Tiger", "Goat", "Dog"};
    int timer = 5;
    int updatetimer = rand() % 100 + 1;



    bool printable = false;
    IRoutingTable *routingTabler = nullptr;

};
// The module class needs to be registered with OMNeT++
Define_Module(Txc2);

void Txc2::initialize()
{
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.

    // Am I Tic or Toc?
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.
        cMessage *msg = new cMessage("pubMsg");
        EV << "Sending initial message\n";
        credA(msg);
        // The handleMessage() method is called whenever a message arrives
        // at the module. Here, we just send it to the other module, through
        // gate `out'. Because both `tic' and `toc' does the same, the message
        // will bounce between the two.

        if((Pc>=3.0)/*&& (fake=='t')*/)
            sendDirect(msg, gate("txc2In"));

}

void Txc2::handleMessage(cMessage *msg)
{
    cMessage *msgs;
    cMessage *msgss = new cMessage("subReturn");
    if(strcmp(msg->getName(),"pubMsg")==0){
                credB(msg);
                sendDirect(msgss, gate("txc2In"));
            }

    else if(strcmp(msg->getName(),"subReturn")==0){
           cancelAndDelete(msg);
           receives();
        }
}


void Txc2::receives(){

    cMessage *msg = new cMessage("pubMsg");
    credC(msg);
    credA(msg);
    if(Pc>=3.0)
        sendDirect(msg, gate("txc2In"));

}

void Txc2::credA(cMessage *msg){
    myfile.open("creda.txt",  std::ofstream::out | std::ofstream::app);



                if (myfile.is_open())
                      {
                        std::string s = genText();
                        myfile<<s<<"\t";
                        screen_name =genScreenName();
                        myfile<<screen_name<<"\t";
                        user_language = genUserLanguage();
                        myfile<<user_language<<"\t";
                        language = genLanguage();
                        myfile<<language<<"\t";
                        timezone = genTimezone();
                        myfile<<timezone<<"\t";
                        location = genLocation();
                        myfile<<location<<"\t";
                        fake = genFake();
                        myfile<<fake<<"\t";
                        myfile<<friends_count<<"\t";
                        friends_count = genFriends();
                        myfile<<compareText(s,animals)<<"\t";
                        myfile<<msg->getFullPath()<<"\t";
                        myfile<<genCreatedAt();
                        myfile.close();
                      }
                else std::cout << "Unable to open files";

                if(updatetimer==0){
                        update();
                        updatetimer = rand() % 100 + 1;
                    }
                    else{
                        updatetimer--;
                    }
}

void Txc2::credB(cMessage *msg){

    myfiles.open("credsb.txt", std::ofstream::out | std::ofstream::app);
    int rating=0;
    int eye=0;
    double eyes =0.0;
    if (myfiles.is_open())
                                  {
                              myfiles<<favourites_count<<"\t";
                              favourites_count = genFavourites();
                              myfiles<<listed_count<<"\t";
                              listed_count = genListed();
                              myfiles<<statuses_count<<"\t";
                              statuses_count = genStatuses();
                              myfiles<<followers_count<<"\t";
                              followers_count = genFollowers();
                              rating = genMessageRating();
                              myfiles<<rating<<"\t";
                              label = genLabel();
                              myfiles<<label<<"\t";
                              eye = genEyewitnessRating(label);
                              myfiles<<eye<<"\t";
                              eyes = eyeRate(eye, Pc);
                              myfiles<<eyes<<"\t";
                              myfiles<<msg->getFullPath()<<"\n";
                              myfiles.close();
                            }
                       else std::cout << "Unable to open files";

                        eyeRatings[numEye]=eyes;
                        ratings[numRatings] = rating;
                        numRatings++;
                        numEye++;

}

void Txc2::credC(cMessage *msg){
    myfiless.open("credssc.txt", std::ofstream::out | std::ofstream::app);
    //if(timer==0){
            Pc = credScore(ratings, mRatings, numRatings, numMessages, Pc);
            Ec = eyeTruth(eyeRatings, numEye);
            myfiless<<Pc<<"\t"<<Ec<<"\t";
            myfiless<<msg->getFullPath()<<"\n";
            /*timer=5;
        }
        else{
            timer--;
        }*/
        myfiless.close();

}

void Txc2::update(){

    friends_count = genFriends();
    favourites_count = genFavourites();
    listed_count = genListed();
    statuses_count = genStatuses();
    followers_count = genFollowers();
    ratings[numRatings] = genMessageRating();
    numRatings++;
    label = genLabel();
    eyeRatings[numEye]=eyeRate(genEyewitnessRating(label), Pc);
    numEye++;
    Pc = credScore(ratings, mRatings, numRatings, numMessages, Pc);
    Ec = eyeTruth(eyeRatings, numEye);


}

char Txc2::genFake (){

    double val=0.0;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<> dis(0.0, 10.0);
    val = dis(generator);

    char str;


    if (val <=0.343)
        str = 't';
    else
        str = 'f';

    return str;
}

int Txc2::genFavourites (){


    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::poisson_distribution<int> distribution(8635.193436);
    int val = distribution(generator);
    favourites_count +=val;

    return val;
}

int Txc2::genListed (){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::poisson_distribution<int> distribution(98.52362009);
    int val = distribution(generator);
    listed_count +=val;

    return val;
}

int Txc2::genStatuses (){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::poisson_distribution<int> distribution(39645.32621);
    int val = distribution(generator);
    statuses_count +=val;

    return val;
}

int Txc2::genFollowers (){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::poisson_distribution<int> distribution(12693.11338);
    int val = distribution(generator);
    followers_count +=val;

    return val;
}

int Txc2::genFriends (){


    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::poisson_distribution<int> distribution(1294.923918);
    int val = distribution(generator);
    friends_count +=val;

    return val;
}

int Txc2::genMessageRating()
{

int val=0;
    val = rand() % 5 + 1;

    return val;

}

int Txc2::genEyewitnessRating(std::string label )
{

    int vals =0;

    if(label.compare("direct-eyewitness")==0 || label.compare("indirect-eyewitness")==0){

        vals = rand() % 3 + 1;
    }

    return vals;

}

std::string Txc2::genTimezone()
{

int val=0;
    val = rand() % 102 + 1;

    std::string str;


    if (val <=56)
        str = "Eastern Standard Time";
    else
        str = "Central Standard Time";

    return str;

}

std::string Txc2::genLocation()
{

int val=0;
    val = rand() % 102 + 1;

    std::string str;


    if (val <=56)
        str = "Trinidad & Tobago";
    else
        str = "Barbados";

    return str;

}

std::string Txc2::genSource()
{

int val=0;
    val = rand() % 129 + 1;

    std::string str;


    if (val <=56)
        str = "https://www.edition.cnn.com/";
    else
        str = "https://www.wikipedia.org/";

    return str;

}

std::string Txc2::genUserLanguage()
{

int val=0;
    val = rand() % 5 + 1;

    std::string str;


    switch (val){
    case(1):
        str = "EN";
        break;
    case(2):
        str = "ES";
        break;
    case(3):
        str = "FR";
        break;
    case(4):
        str = "HI";
        break;
    case(5):
        str = "JA";
        break;
    }
    return str;

}

std::string Txc2::genLanguage()
{

int val=0;
    val = rand() % 5 + 1;

    std::string str;


    switch (val){
    case(1):
        str = "EN";
        break;
    case(2):
        str = "ES";
        break;
    case(3):
        str = "FR";
        break;
    case(4):
        str = "HI";
        break;
    case(5):
        str = "JA";
        break;
    }
    return str;

}

std::string Txc2::genLabel()
{

    int val=0;
    val = rand() % 3 + 1;
    std::string str;


    switch(val){
               case(1):
               str = "non-eyewitness";
               break;
               case(2):
               str = "indirect-eyewitness";
               break;
               case(3):
               str = "direct-eyewitness";
               break;
               default:
               str = "don't know";
               break;
    }

    return str;

}


char Txc2::genRandom()  // Random string generator function.
{
    static const char alphanum[] =
    "0123456789"
    "!@#$%^&*"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

    int stringLength = sizeof(alphanum) - 1;


    return alphanum[rand() % stringLength];
}

std::string Txc2::genText()
{
    srand(time(0));
    std::string Str;
    for(int z=0; z < 21; z++)
    {
        Str+= genRandom();

    }
    return Str;

}

std::string Txc2::genScreenName()
{
    srand(time(0));
    std::string Str;
    for(int z=0; z < 21; z++)
    {
        Str+= genRandom();

    }
    return Str;

}

char * Txc2::genCreatedAt()
{
    // current date/time based on current system
      time_t now = time(0);

      // convert now to string form
      char* dt = ctime(&now);

      return dt;

}

int Txc2::incrementVal(int nv){

    return nv++;
}

double Txc2::credScore(int ratings[], double mRatings[], int numRatings, int numMessages, double Pc){

    int msum = 0;
    int vsum = 0;
    int psum = 0;
    int ssum = 0;
    double z = 1.96;
    for (int i=0; i<numRatings; i++){
        msum = msum + ratings[i];
    }
    double Mm = abs(msum/numRatings);
    double Mmm = sMm;
    sMm = ((snumRatings*Mmm) + (numRatings*Mm))/(snumRatings+numRatings);

    for (int i=0; i<numRatings; i++){
            vsum = vsum + ((ratings[i]-Mm)*(ratings[i]-Mm));
        }
    double Msd = vsum/numRatings;
    double Mmsd = (sMsd*sMsd);
    double Mmmsd = ((numRatings*((Msd)+((Mm - sMm)*(Mm - sMm))))+(snumRatings*((Mmsd)+((Mmm - sMm)*(Mmm - sMm)))))/(numRatings+snumRatings);
    sMsd = sqrt(abs(Mmmsd));
    snumRatings = snumRatings + numRatings;
    double Mc = sMm + z*(sMsd/sqrt(snumRatings));
    numRatings = 0;
    mRatings[numMessages] = Mc;
    numMessages++;
    for (int i=0; i<numMessages; i++){
            psum = psum + mRatings[i];
        }
    double Pm = psum/numMessages;
    for (int i=0; i<numMessages; i++){
            ssum = ssum + ((mRatings[i]-Pm)*(mRatings[i]-Pm));
            }
        double Psd = sqrt(abs(ssum/numMessages));
        double Pcn = Pm + z*(Psd/sqrt(numMessages));
        return Pcn;

}

float Txc2::getMold(const std::vector<char>& vec){   //Find the modulus length of the vector
      int n = vec.size();
      float sum = 0.0;
      for (int i = 0; i<n; ++i)
          sum += vec[i] * vec[i];
      return sqrt(sum);
  }

float Txc2::getSimilarity(const std::vector<char>& lhs, const std::vector<char>& rhs){
      int n = lhs.size();
      float tmp = 0.0;  //Inner product
      for (int i = 0; i<n; ++i)
          tmp += lhs[i] * rhs[i];
      return tmp / (getMold(lhs)*getMold(rhs));
  }

double Txc2::compareText (std::string message, std::vector<std::string> keywords){

        std::vector<char> vm;
        std::vector<char> vk;
        std::vector<char>::iterator it;
        std::vector<char>::iterator its;
        double Ms = 0.0;
        double Ws = 0.0;
        int count=0;

        it = vm.begin();
        vm.insert(it, message.cbegin(), message.cend());
        count= 1+std::count (vm.begin(), vm.end(), ' ');
        for(int i=0; i<keywords.size(); i++){
            its = vk.begin();
            vk.insert(its, keywords[i].cbegin(), keywords[i].cend());
            Ws = Ws + getSimilarity(vm, vk);
        }
        Ms = Ms +(Ws/keywords.size());

        Ms = Ms/count;
        return Ms;
}

double Txc2::eyeRate(int eyeRating, double Pc){
    return Pc*eyeRating;
}

double Txc2::eyeTruth(double eyeRatings[], int numEye){
        int emsum = 0;
        int evsum = 0;
        double z = 1.96;

        for (int i=0; i<numEye; i++){
            emsum = emsum + eyeRatings[i];
        }
        double em = emsum/numEye;
        double emm = eMm;
            eMm = ((numEyes*emm) + (numEye*em))/(numEyes+numEye);
        for (int i=0; i<numEye; i++){
            evsum = evsum + ((eyeRatings[i]-em)*(eyeRatings[i]-em));
            }
        double esd = evsum/numEye;
        double eesd = (eMsd*eMsd);
        double eeesd = ((numEye*((esd)+((em - eMm)*(em - eMm))))+(numEyes*((eesd)+((emm - eMm)*(emm - eMm)))))/(numEye+numEyes);
        eMsd = sqrt(abs(eeesd));
        numEyes = numEyes + numEye;
        numEye=0;

        double Ecn = eMm + z*(eMsd/sqrt(numEyes));
            return Ecn;
}
