#!/usr/bin/perl

$argc = @ARGV; # counting elements in @ARGV
if ($argc != 2) {
    print "usage: markov.pl [output_length] [prefix_length]\n";
    exit;
}

$out_len = $ARGV[0];
$pref_len = $ARGV[1];

srand($out_len * 98123756);

undef $/;
$_=<STDIN>;
@inp = split;

@st = ();

foreach $w (@inp) {
    $st_str = join(' ', @st);
    if (!exists($tbl{$st_str})) {
        $tbl{$st_str} = [$w];
    } else {
        push(@{$tbl{$st_str}}, $w);
    }
    
    push(@st, $w);
    if (scalar (@st) > $pref_len) {
        shift(@st);
    }
}

#foreach $t (keys %tbl) {
#    print "'".$t."' - ";
#    print join('; ', @{$tbl{$t}});
#    print "\n";
#}

@st = ();
for ($i = 0; $i < $out_len; $i++) {
    $st_str = join(' ', @st);
    exit if !exists($tbl{$st_str});

    @words = @{$tbl{$st_str}};
    $j = rand @words;
    $w = $words[$j];

    print "$w ";
    
    push(@st, $w);
    if (scalar (@st) > $pref_len) {
        shift(@st);
    }
}
