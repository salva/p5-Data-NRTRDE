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

Data::NRTRDE - Parser for NRTRDE files.

=head1 SYNOPSIS

  use Data::NRTRDE qw(parse_nrtrde);
  my $data = parse_nrtrde($buffer);

=head1 DESCRIPTION

This module parsers NRTRDE (Near Real Time Roaming Data Exchange)
files and converts them into Perl data structures.

=head2 EXPORT

The following subroutines can be imported from this module:

=over 4

=item $data = parse_nrtrde($buffer)

parses the NRTRDE data in the given buffer and returns it as a Perl
data structure.

=back

=head1 SEE ALSO

NRTRDE TD.35 specification from the GSM Association... if you
can (they don't make the specification publicly available).

=head1 AUTHOR

Salvador Fandiño, E<lt>sfandino@yahoo.comE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2014 by Qindel Formación y Servicios S.L.

This Perl module is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This Perl module is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this package. If not, see L<http://www.gnu.org/licenses/>.

=cut
