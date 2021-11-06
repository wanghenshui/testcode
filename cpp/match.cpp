int matchstar(int c, char * regexp, char * text);
// 在text 开头找 regexp
int matchhere(char * regexp, char * text){
	if (regexp[0] == '\0') return 1;
	if (regexp[1] == '*') return matchstar(regexp[0],regexp+2,text);
	if (regexp[0] == '$' && regexp[1] == '\0') return *text++ == '\0';
	if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text)) return matchhere(regexp+1,text+1);
	return 0;
}	
//match star
int matchstar(int c, char * regexp, char * text){
	do {
		if (matchhere(regexp,text)) return 1;
	} while (*text != '\0' && (*text++ == c || c == '.'));
}
int match(char *regexp, char *text){
	if (regexp[0] == '^')
		return matchhere(regexp+1, text);

	do {
		if (matchhere(regexp, text))
			return 1;
	} while (*text++ != '\0');
	return 0;
}