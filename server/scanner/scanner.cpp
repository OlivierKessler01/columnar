#include "scanner.h"
#include "generator.h"
#include <string>
#include <vector>
#include <sys/syslog.h>

int rollback(int &last_accept_idx, token &accept_token, unsigned int &i, string &buffer, Tokens &tokens){
	if (last_accept_idx == -1){
		syslog(LOG_INFO, "Invalid synthax:");
		return -1;
	}
	tokens.tokens.push_back(accept_token);
	//Reset the buffer for next word
	i=last_accept_idx+1;
	last_accept_idx=-1;
	buffer="";
	accept_token={"", unknown};
	return 0;
}

/**
 * lexe - Given a request and a list of tokens allocated on the heap
 *
 */
ssize_t lexe(Tokens &tokens, string input) 
{
	string state = "16465105051891388374";
	unsigned int i = 0;
	char c = 0;
	token accept_token = token{"",unknown};
	string buffer = "";
	int last_accept_idx = -1;
	unsigned int glob_last_accept_idx = -1;
	//Adding a space to enable munching token on last input
	input += " ";

	while (i < input.size()) {
		c=input[i];
		if (state == "11119396927836121025"){
			accept_token=token{buffer,keyword};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "14554294423191716341"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "11119396927836121025";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "17503321066619012476"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "16397472949894876630";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "3582797868027595582"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "17503321066619012476";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "15748485969345367873"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "13382696477803903196"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "16843946196484477036"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "12927415188419503156"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "4165126874377763481"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "3809997115066456306"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "13875296041825097965"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "6142509188972423790"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "11139190344061183764"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "3765438742796532688"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "16397472949894876630"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "14554294423191716341";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "4364061394201320532"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "17350183369529245971"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "16587899564387224734"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "1721114500600935234"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "16313874748603954589";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "2233972945074121005"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "16465105051891388374"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "2233972945074121005";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "3582797868027595582";buffer+=c;i++;continue;
			if (c == '6') state = "2625988258024215026";buffer+=c;i++;continue;
			if (c == '7') state = "15748485969345367873";buffer+=c;i++;continue;
			if (c == '8') state = "13382696477803903196";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "12927415188419503156";buffer+=c;i++;continue;
			if (c == 's') state = "5806758910215087169";buffer+=c;i++;continue;
			if (c == '0') state = "3765438742796532688";buffer+=c;i++;continue;
			if (c == '1') state = "13464939651923598199";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "2452783702702214719";buffer+=c;i++;continue;
			if (c == '2') state = "15565266830116869941";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "16291100551854849634";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "4165126874377763481";buffer+=c;i++;continue;
			if (c == ';') state = "14259944108807411449";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "15927871353235858372"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "11678633246446006186"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "15565266830116869941"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "16291100551854849634"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "14259944108807411449"){
			accept_token=token{buffer,endline};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "9478052861934609119"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "10522500447331663428";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "610615940123804345"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "1721114500600935234";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "2625988258024215026"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "16313874748603954589"){
			accept_token=token{buffer,keyword};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "1729136448206813849"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "5806758910215087169"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "9478052861934609119";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "13464939651923598199"){
			accept_token=token{buffer,integer};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "15927871353235858372";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "4364061394201320532";buffer+=c;i++;continue;
			if (c == '7') state = "11139190344061183764";buffer+=c;i++;continue;
			if (c == '8') state = "16843946196484477036";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "1729136448206813849";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "16587899564387224734";buffer+=c;i++;continue;
			if (c == '1') state = "17350183369529245971";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "11678633246446006186";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "3809997115066456306";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "13875296041825097965";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "2862987720383924690"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "12641079979473037463";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "12641079979473037463"){
			accept_token=token{buffer,keyword};
			last_accept_idx=i;
			glob_last_accept_idx=i;
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "2452783702702214719"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "610615940123804345";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "10522500447331663428"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "5076569105217356487";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "6142509188972423790";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (state == "5076569105217356487"){
			if (i == input.size()-1) {
				//force rollback on artificially added last char
				int r = rollback(last_accept_idx, accept_token, i, buffer,tokens);
				if (r != 0) {
					return r;
				}
			}
			if (c == '5') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'o') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'w') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '6') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '7') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '8') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'r') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '9') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 's') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '0') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '1') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'e') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'f') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '2') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'l') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 't') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '3') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'm') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'h') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == '4') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == ';') state = "6142509188972423790";buffer+=c;i++;continue;
			if (c == 'c') state = "2862987720383924690";buffer+=c;i++;continue;
			int r = rollback(last_accept_idx, accept_token, i, buffer, tokens);
			if (r != 0) {
				return r;
			}
		}
		if (tokens.tokens.size() == 0 || glob_last_accept_idx != input.size() -2){
			syslog(LOG_INFO, "Invalid synthax: ");
			return -1;
		}
	}
    return 0;
}
