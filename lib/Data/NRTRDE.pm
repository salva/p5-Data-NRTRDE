package Data::NRTRDE;

our $VERSION = '0.01';

use strict;
use warnings;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT_OK = qw(parse_nrtrde);

require XSLoader;
XSLoader::load('Data::NRTRDE', $VERSION);

1;

__END__

=head1 NAME

Data::NRTRDE - Perl extension for blah blah blah

=head1 SYNOPSIS

  use Data::NRTRDE;
  blah blah blah

=head1 DESCRIPTION

Stub documentation for Data::NRTRDE, created by h2xs. It looks like the
author of the extension was negligent enough to leave the stub
unedited.

Blah blah blah.

=head2 EXPORT

None by default.



=head1 SEE ALSO

Mention other useful documentation such as the documentation of
related modules or operating system documentation (such as man pages
in UNIX), or any relevant external documentation such as RFCs or
standards.

If you have a mailing list set up for your module, mention it here.

If you have a web site set up for your module, mention it here.

=head1 AUTHOR

Salvador Fandiño, E<lt>salva@E<gt>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2014 by Salvador Fandiño

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.18.2 or,
at your option, any later version of Perl 5 you may have available.


=cut
