#include "scanner.h"
#include "generator.h"
#include <string>
#include <vector>
#include <sys/syslog.h>
/**
 * lexe - Given a request and a list of tokens allocated on the heap
 *
 */
ssize_t lexe(Tokens &tokens, string input) 
{
	string state = "16040776805222689698";
	int i = 0;
	char c = 0;
	string last_accept = "";
	int last_accept_idx = -1;
	std::unordered_map<string, synthax_cat> accept = {
		{"9279914861003325328", integer},
		{"15130017063074828240", integer},
		{"2471182208867795348", keyword},
		{"15839846693641764761", integer},
		{"17845054529581772674", keyword},
		{"6443369355447147189", integer},
		{"8153693426373465628", endline},
		{"10102304779275121860", integer},
		{"11878216088891700056", integer},
		{"9029432081993790722", integer},
		{"5080664090826229952", integer},
		{"1205657766059198990", integer},
		{"4813048681821323622", integer},
		{"8497311409368630306", integer},
		{"5640777688317388534", integer},
		{"13188546403351721604", integer},
		{"17775277504424632816", integer},
		{"1168454399044110270", integer},
		{"12676948136493166004", keyword},
		{"17592989463927491088", integer},
		{"2972310534898803288", integer},
		{"6918091281739002035", integer},
		{"572625671489022598", integer},
		{"2298084731971518653", integer},
	};

	while (i < input.size()) {
		c=input[i];
		if (state == "6918091281739002035"){
			last_accept="6918091281739002035";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "12676948136493166004"){
			last_accept="12676948136493166004";
			last_accept_idx=i;
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "14533700784540903547"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "12676948136493166004";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "17717318921040501926"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "7016072257758017171";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "13551994182354987898"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "17717318921040501926";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "15130017063074828240"){
			last_accept="15130017063074828240";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "5640777688317388534"){
			last_accept="5640777688317388534";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "8497311409368630306"){
			last_accept="8497311409368630306";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "1168454399044110270"){
			last_accept="1168454399044110270";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "16378686346219296116"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "11591814184321034120";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "17592989463927491088"){
			last_accept="17592989463927491088";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "7253636363568632490"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "2471182208867795348";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "6142509188972423790"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "9029432081993790722"){
			last_accept="9029432081993790722";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "13188546403351721604"){
			last_accept="13188546403351721604";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "11878216088891700056"){
			last_accept="11878216088891700056";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "7638997972794786334"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "2129797251336995545";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "10102304779275121860"){
			last_accept="10102304779275121860";
			last_accept_idx=i;
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "2972310534898803288"){
			last_accept="2972310534898803288";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "16040776805222689698"){
			if (c == '5') state = "6918091281739002035";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "13551994182354987898";i++;continue;
			if (c == '6') state = "9279914861003325328";i++;continue;
			if (c == '7') state = "15839846693641764761";i++;continue;
			if (c == '8') state = "15130017063074828240";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6443369355447147189";i++;continue;
			if (c == 's') state = "7776764368134489843";i++;continue;
			if (c == '0') state = "10102304779275121860";i++;continue;
			if (c == '1') state = "2972310534898803288";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "16378686346219296116";i++;continue;
			if (c == '2') state = "2298084731971518653";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "572625671489022598";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "11878216088891700056";i++;continue;
			if (c == ';') state = "8153693426373465628";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "2129797251336995545"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "7253636363568632490";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "15839846693641764761"){
			last_accept="15839846693641764761";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "2298084731971518653"){
			last_accept="2298084731971518653";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "4813048681821323622"){
			last_accept="4813048681821323622";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "572625671489022598"){
			last_accept="572625671489022598";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "1205657766059198990"){
			last_accept="1205657766059198990";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "8153693426373465628"){
			last_accept="8153693426373465628";
			last_accept_idx=i;
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "5080664090826229952"){
			last_accept="5080664090826229952";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "6443369355447147189"){
			last_accept="6443369355447147189";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "17775277504424632816"){
			last_accept="17775277504424632816";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "11591814184321034120"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "1926534826714537371";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "1926534826714537371"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "17845054529581772674";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "7016072257758017171"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "14533700784540903547";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "7776764368134489843"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "2319408897019528809";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "17845054529581772674"){
			last_accept="17845054529581772674";
			last_accept_idx=i;
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "2319408897019528809"){
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "7638997972794786334";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "9279914861003325328"){
			last_accept="9279914861003325328";
			last_accept_idx=i;
			if (c == '5') state = "8497311409368630306";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "9029432081993790722";i++;continue;
			if (c == '7') state = "4813048681821323622";i++;continue;
			if (c == '8') state = "5640777688317388534";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "17775277504424632816";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "17592989463927491088";i++;continue;
			if (c == '1') state = "1205657766059198990";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "1168454399044110270";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "5080664090826229952";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "13188546403351721604";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (state == "2471182208867795348"){
			last_accept="2471182208867795348";
			last_accept_idx=i;
			if (c == '5') state = "6142509188972423790";i++;continue;
			if (c == 'o') state = "6142509188972423790";i++;continue;
			if (c == 'w') state = "6142509188972423790";i++;continue;
			if (c == '6') state = "6142509188972423790";i++;continue;
			if (c == '7') state = "6142509188972423790";i++;continue;
			if (c == '8') state = "6142509188972423790";i++;continue;
			if (c == 'r') state = "6142509188972423790";i++;continue;
			if (c == '9') state = "6142509188972423790";i++;continue;
			if (c == 's') state = "6142509188972423790";i++;continue;
			if (c == '0') state = "6142509188972423790";i++;continue;
			if (c == '1') state = "6142509188972423790";i++;continue;
			if (c == 'e') state = "6142509188972423790";i++;continue;
			if (c == 'f') state = "6142509188972423790";i++;continue;
			if (c == '2') state = "6142509188972423790";i++;continue;
			if (c == 'l') state = "6142509188972423790";i++;continue;
			if (c == 't') state = "6142509188972423790";i++;continue;
			if (c == '3') state = "6142509188972423790";i++;continue;
			if (c == 'm') state = "6142509188972423790";i++;continue;
			if (c == 'h') state = "6142509188972423790";i++;continue;
			if (c == '4') state = "6142509188972423790";i++;continue;
			if (c == ';') state = "6142509188972423790";i++;continue;
			if (c == 'c') state = "6142509188972423790";i++;continue;
			//rollback if no transition on c
			if (last_accept_idx == -1){
				syslog(LOG_INFO, "Invalid synthax:"+input);
				return -1;
			}
			//Reset the buffer for next word
			i=last_accept_idx+1;
			last_accept_idx=-1;
			last_accept="";
		}
		if (tokens.tokens.size() == 0 || last_accept_idx != input.size() -1){
			syslog(LOG_INFO, "Invalid synthax: "+ input);
			return -1;
		}
    return 0;
}
