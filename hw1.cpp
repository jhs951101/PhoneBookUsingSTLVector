#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const int MAX_CONTACT_ENTRY = 100;

string nameData[] = {"K Honoka", "S Umi", "M Kotori", "N Maki", "H Rin",
				  "K Hanayo", "T Nozomi", "A Eri", "Y Nico", "JH Shim"};
int numberData[] = {3958, 2573, 2850, 1649, 9274, 1627, 9742, 4839, 2785, 1049};
string emailData[] = {
		"kHonoka@lovelive.com", "sUmi@lovelive.com", "mKotori@lovelive.com", "nMaki@lovelive.com", "hRin@lovelive.com",
		"kHanayo@lovelive.com", "tNozomi@lovelive.com", "aEri@lovelive.com", "yNico@lovelive.com", "tails1101@naver.com"
		};

class ValueInfo {
public:
	int phoneNumber;
	string emailAddress;
	ValueInfo(){
		phoneNumber = -99;
	}
	ValueInfo(int n, string em){
		phoneNumber = n;
		emailAddress = em;
	}
};

ValueInfo viNull;

class Entry {
public:
	string phoneName;
	ValueInfo valueInfo;
	Entry(){
		phoneName = "";
		valueInfo.phoneNumber = -1;
		valueInfo.emailAddress = "";
	}
	Entry(string s, int n, string em) {
		phoneName = s;
		valueInfo.phoneNumber = n;
		valueInfo.emailAddress = em;
	}
};

vector<Entry> phoneBookInfos;

void insert(string name, int number, string email);
void remove(string name);
void update(string name, int number, string email);
int findPhoneNumber(string name);
string findEmailAddress(string name);
string findName(int number);
string findName(string email);

int findLocFromNumber(int number){
	for (int i=0; i<phoneBookInfos.size(); ++i){
		if (phoneBookInfos[i].valueInfo.phoneNumber == number)
			return i;
	}
	return -1; // not found
}

int findLocFromEmail(string email){
	for (int i=0; i<phoneBookInfos.size(); ++i){
		if (phoneBookInfos[i].valueInfo.emailAddress == email)
			return i;
	}
	return -1; // not found
}

int findLoc(string name){
	for (int i=0; i<phoneBookInfos.size(); ++i){
		if (phoneBookInfos[i].phoneName == name)
			return i;
	}
	return -1; // not found
}

ValueInfo find(string name){
	int loc = findLoc(name);
	if (loc == -1)
		return viNull; // not found
	return phoneBookInfos[loc].valueInfo;
}

int findPhoneNumber(string name){
	int loc = findLoc(name);
	if (loc == -1)
		return -1; // not found
	return phoneBookInfos[loc].valueInfo.phoneNumber;
}

string findEmailAddress(string name){
	int loc = findLoc(name);
	if (loc == -1)
		return ""; // not found
	return phoneBookInfos[loc].valueInfo.emailAddress;
}

string findName(int number){
	int loc = findLocFromNumber(number);

	if(loc == -1)
		return "";

	return phoneBookInfos[loc].phoneName;
}

string findName(string email){
	int loc = findLocFromEmail(email);

	if(loc == -1)
		return "";

	return phoneBookInfos[loc].phoneName;
}

void insert(string name, int number, string email){
	int loc = findLoc(name);
	if (loc == -1){ // insert
		if (phoneBookInfos.size() > MAX_CONTACT_ENTRY){
			cout << "***Error -- PhoneBook Overflow" << endl;
		}
		else {
			Entry e(name, number, email);
			phoneBookInfos.push_back(e);
		}
	}
	else {
		cout << "***Error -- Duplicated Name" << endl;
	}
}

void remove(string name){
	int loc = findLoc(name);
	if (loc != -1){ // there exist name
		// remove array entry at loc
		for (int i=loc+1; i<phoneBookInfos.size(); ++i){
			phoneBookInfos[i-1].phoneName = phoneBookInfos[i].phoneName;
			phoneBookInfos[i-1].valueInfo.phoneNumber = phoneBookInfos[i].valueInfo.phoneNumber;
			phoneBookInfos[i-1].valueInfo.emailAddress = phoneBookInfos[i].valueInfo.emailAddress;
		}
		phoneBookInfos.pop_back();
	}
	else {
		cout << "***Error -- Name not found" << endl;
	}
}

void update(string name, int number){
	int loc = findLoc(name);

	if(loc != -1){
		phoneBookInfos[loc].valueInfo.phoneNumber = number;
	}
	else {
		cout << "***Error -- Name not found" << endl;
	}
}

void update(string name, string email){
	int loc = findLoc(name);

	if(loc != -1){
		phoneBookInfos[loc].valueInfo.emailAddress = email;
	}
	else {
		cout << "***Error -- Name not found" << endl;
	}
}

void update(string name, int number, string email){
	update(name, number);
	update(name, email);
}

void listAll(){
	cout.setf(ios::left);

	cout << setw(10) << "Name" << setw(10) << "Number" << setw(20) << "Email" << endl;
	for (int i=0; i<phoneBookInfos.size(); ++i){
		cout << setw(10) << phoneBookInfos[i].phoneName
			 << setw(10) << phoneBookInfos[i].valueInfo.phoneNumber
			 << setw(20) << phoneBookInfos[i].valueInfo.emailAddress << endl;
	}
}

int main ()
{
	int incount = 10;
	for (int i=0; i < incount; ++i){
		insert(nameData[i], numberData[i], emailData[i]);
	}

	// 수정하기 전의  조회

	cout << "삽입된 정보 전체 조회" << endl;
	listAll();
	cout << endl;

	// insert, remove, update

	cout << "이미 존재하는 이름을 insert (error)" << endl;
	insert("K Honoka", 3958, "kHonoka@lovelive.com");
	cout << endl;

	cout << "없는 이름을 insert" << endl;
	insert("S Riko", 6937, "sRiko@loveliveSunshine.com");
	cout << endl;

	cout << "존재하는 이름을 remove" << endl;
	remove("JH Shim");
	cout << endl;

	cout << "존재하지도 않는 이름을 remove (error)" << endl;
	remove("K Ruby");
	cout << endl;

	cout << "존재하는 이름을 update" << endl;
	update("M Kotori", 3672, "kotoriDaisuki@lovelive.com");
	cout << endl;

	cout << "존재하지도 않는 이름을 update (error)" << endl;
	update("T Chika", 2759, "tChika@loveliveSunshine.com");
	cout << endl;

	// 이름으로부터 번호 또는 이메일 주소 찾아내기

	cout << "T Nozomi의 번호는 무엇인가? : " << find("T Nozomi").phoneNumber << endl;
	cout << endl;

	cout << "A Eri의 이메일 주소는 무엇인가? : " << find("A Eri").emailAddress << endl;
	cout << endl;

	// 번호 또는 이메일 주소로부터 이름 찾아내기

	cout << "존재하는 번호로부터 이름 찾아내기" << endl;
	cout << "번호 2785은 누구의 번호인가? : " << findName(2785) << endl;
	cout << endl;

	cout << "존재하지도 않는 번호로부터 이름 찾아내기" << endl;
	cout << "4478은 누구의 번호인가? : " << findName(4478) << endl;
	cout << endl;

	cout << "존재하는 이메일 주소로부터 이름 찾아내기" << endl;
	cout << "nMaki@lovelive.com 은 누구의 이메일 주소인가? : " << findName("nMaki@lovelive.com") << endl;
	cout << endl;

	cout << "존재하지도 않는 이메일 주소로부터 이름 찾아내기" << endl;
	cout << "kHanamaru@loveliveSunshine.com 은 누구의 이메일 주소인가? : " << findName("kHanamaru@loveliveSunshine.com") << endl;
	cout << endl;

	// 수정한 후의  조회

	cout << "수정된 정보 전체 조회" << endl;
	listAll();
	cout << endl;

	return 0;
}
