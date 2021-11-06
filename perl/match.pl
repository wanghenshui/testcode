#!/usr/bin/perl 
while(<>){
	chomp;
	if(/YOUR_MATCH_GOSE_HERE/){
		print "Matched: |$`<$&>$'|\n";
	}else{
		print "NO match\n";
	}
}
