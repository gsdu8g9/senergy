/*******************************************************************************
 *
 *	 This file is part of Senergy.
 *
 *   Senergy is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Senergy is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Senergy. If not, see <http://www.gnu.org/licenses/>.
 *
 *   Swen Kooij (Photonios) <swenkooij@gmail.com> <photonios@outlook.com>
 *
 *******************************************************************************/

#ifndef SY_DNS_RESOURCE_RECORD_TYPES_H
#define SY_DNS_RESOURCE_RECORD_TYPES_H

namespace Senergy
{
namespace Dns
{

/*!
 * \brief An enumuration of all possible resource record types (RR), as defined by IANA.
 * 
 * \see http://www.iana.org/assignments/dns-parameters/dns-parameters.xhtml
 *
 * \author Swen Kooij (Photonios).
 */
enum class ResourceRecordType : unsigned short
{
	/*!
	 * \brief Unknown.
	 */
	Unknown = 0,

	/*!
	 * \brief A host address.
	 */
	A = 1,
	
	/*!
 	 * \brief A authoritative name server.
	 */
	NS = 2,

	/*!
 	 * \brief A mail destination (Obsolete, use MX)
	 */
	MD = 3,
	
	/*!
 	 * \brief A mail forwarder (Obsolete, use MX)
	 */
	MF = 4,
	
	/*!
 	 * \brief The canonical name for an alias.
	 */
	CNAME = 5,

	/*!
	 * \brief Sexueel Overdraagbare Aandoening (Marks the start of a zone of authority).
	 */
	SOA = 6,
	
	/*!
	 * \brief Mailbox domain name (EXPERIMENTAL).
	 */
	MB = 7,

	/*!
	 * \brief Mail group member (EXPERIMENTAL).
	 */
	MG = 8,

	/*!
	 * \brief Mail rename domain name (EXPERIMENTAL).
	 */
	MR = 9,

	/*!
	 * \brief (NULL) - A null Resource Record (RR).
	 */
	NUL = 10,
	
	/*!
	 * \brief Well-known service description.
	 */
	WKS = 11,

	/*!
	 * \brief Domain name pointer.
	 */
	PTR = 12,

	/*!
	 * \brief Host information.
	 */
	HINFO = 13,

	/*!
	 * \brief Mailbox or mail list notification.
	 */
	MINFO = 14,

	/*!
	 * \brief Mail exchange.
	 */
	MX = 15,

	/*!
	 * \brief Text strings.
	 */
	TXT = 16,

	/*!
	 * \brief Responsible person.
	 */
	RP = 17,

	/*!
	 * \brief For AFS database location.
	 */
	AFSDB = 18,

	/*!
	 * \brief For X.25 PSDN addresses.
	 */
	X25 = 19,

	/*!
	 * \brief For ISDN addresses.
	 */
	ISDN = 20,

	/*!
	 * \brief Route-through.
	 */
	RT = 21,

	/*!
	 * \brief NSAP Address, for NSAP style A records.
	 */
	NSAP = 22,

	/*!
	 * \brief Domain pointer, NSAP style.
	 */
	NSAP_PTR = 23,
	
	/*!
 	 * \brief Domain name signature.
	 */
	SIG = 24,

	/*!
	 * \brief Security key.
	 */
	KEY = 25,

	/*!
	 * \brief X.400 mail mapping information.
	 */
	PX = 26,

	/*!
 	 * \brief Geographical position.
	 */
	GPOS = 27,

	/*!
	 * \brief IPV6 Address.
	 */
	AAAA = 28,

	/*!
 	 * \brief Location finformation.
	 */
	LOC = 29,

	/*!
	 * \brief Next domain (Obsolete).
	 */
	NXT = 30,

	/*!
 	 * \brief End point identifier.
	 */
	EID = 31,

	/*!
 	 * \brief Nimloc locator.
	 */
	NIMLOC = 32,

	/*!
 	 * \brief Server selection.
	 */
	SRV = 33,

	/*!
	 * \brief ATM Address.
	 */
	ATMA = 34,

	/*!
	 * \brief Naming authority pointer.
	 */
	NAPTR = 35,

	/*!
 	 * \brief Key exchanger.
	 */
	KX = 36,

	/*!
	 * \brief CERT.
	 */
	CERT = 37,

	/*!
	 * \brief A6 (OBSOLETE, use AAAA).
	 */
	A6 = 38,

	/*!
	 * DNAME.
	 */
	DNAME = 39,

	/*!
	 * \brief SINK.
	 */
	SINK = 40,

	/*!
	 * \brief OPT.
	 */
	OPT = 41,

	/*!
	 * \brief APL.
	 */
	APL = 42,

	/*!
 	 * \brief Delegation signer.
	 */
	DS = 43,

	/*!
	 * \brief SSH Key Fingerprint.
	 */
	SSHFP = 44,

	/*!
	 * \brief IPSEC Key.
	 */
	IPSECKEY = 45,

	/*!
 	 * \brief RRSIG.
	 */
	RRSIG = 46,

	/*!
	 * \brief NSEC.
	 */
	NSEC = 47,

	/*!
	 * \brief DNS Key.
	 */
	DNSKEY = 48,

	/*!
	 * \brief DHCID.
	 */
	DHCID = 49,

	/*!
	 * \brief NSEC3.
	 */
	NSEC3 = 50,

	/*!
	 * \brief NSEC3PARAM.
	 */
	NSEC3PARAM = 51,

	/*!
	 * \brief TLSA.
	 */
	TLSA = 52,

	// 53 - 54 Unassinged.

	/*!
	 * \brief Host identify protocol.
	 */
	HIP = 55,

	/*!
	 * \brief NINFO.
	 */
	NFINO = 56,

	/*!
	 * \brief RKEY.
	 */
	RKEY = 57,

	/*!
 	 * \brief Trust anchor link.
	 */
	TALINK = 58,

	/*!
 	 * \brief Child DS.
	 */
	CDS = 59,

	// 60 - 98 Unassigned.
	
	/*!
	 * \brief SPF (IANA-Reserved).
	 */
	SPF = 99,

	/*!
	 * \brief UINFO (IANA-Reserved).
	 */
	UINFO = 100,

	/*!
	 * \brief UID (IANA-Reserved).
	 */
	UID = 101,

	/*!
	 * \brief GID (IANA-Reserved).
	 */
	GID = 102,

	/*!
 	 * \brief UNSPEC (IANA-Reserved).
	 */
	UNSPEC = 103,

	/*!
	 * \brief NID.
	 */
	NID = 104,

	/*!
	 * \brief L32.
	 */
	L32 = 105,
	
	/*!
	 * \brief L64.
	 */
	L64 = 106,

	/*!
	 * \brief LP.
	 */
	LP = 107,

	/*!
	 * \brief EUI48 address.
	 */
	EUI48 = 108,

	/*!
 	 * \brief EUI64 address.
	 */
	EUI64 = 109,

	// 110 - 248 Unassigned.
	
	/*!
 	 * \brief Transaction key.
	 */
	TKEY = 249,

	/*!
	 * \brief Transaction signature.
	 */
	TSIG = 250,

	/*!
	 * \brief Incremental transfer
	 */
	IXFR = 251,

	/*!
	 * \brief Transfer of an entire zone.
 	 */
	AXFR = 252,

	/*!
	 * \brief Mailbox-related resource records (RR) (Obsolete, see MX).
	 */
	MAILB = 253,

	/*!
 	 * \brief Mail agent resource records (RR) (Obsolete, see MX).
	 */
	MAILA = 254,

	/*!
	 * \brief A request for all records the server/cache has available.
	 */
	ALL_RECORDS = 255,

	/*!
	 * \brief URI.
	 */
	URI = 256,

	/*!
	 * \brief Certificate authority restriction.
	 */
	CAA = 257,
	
	// 258 - 32767 Unassigned

	/*!
	 * \brief DNSSEC Trust authorities.
	 */
	TA = 32768,

	/*!
	 * \brief DNSSEC Lookaside validation.
	 */
	DLV = 32769,
};

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_RESOURCE_RECORD_TYPES_H
