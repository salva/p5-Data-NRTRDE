use 5.008;
use ExtUtils::MakeMaker;

WriteMakefile( NAME          => 'Data::NRTRDE',
	       VERSION_FROM  => 'lib/Data/NRTRDE.pm',
	       PREREQ_PM     => {},
	       ABSTRACT_FROM => 'lib/Data/NRTRDE.pm',
	       AUTHOR        => 'Salvador Fandiño <sfandino@yahoo.com>',
	       LIBS          => [''],
	       DEFINE        => '',
	       INC           => '-I.',
	       OBJECT        => '$(O_FILES)',
    );
