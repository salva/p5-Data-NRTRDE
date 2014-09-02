use 5.008;
use ExtUtils::MakeMaker;

my %prereq_pm;
use Config;

if ($Config{ivsize} < 8) {
    $prereq_pm{'Math::Int64'} = '0.30';
}

WriteMakefile( NAME          => 'Data::NRTRDE',
	       VERSION_FROM  => 'lib/Data/NRTRDE.pm',
	       PREREQ_PM     => \%prereq_pm,
	       ABSTRACT_FROM => 'lib/Data/NRTRDE.pm',
	       AUTHOR        => 'Salvador Fandiño <sfandino@yahoo.com>',
	       LIBS          => [''],
	       DEFINE        => '',
	       INC           => '-I.',
	       OBJECT        => '$(O_FILES)',
    );
