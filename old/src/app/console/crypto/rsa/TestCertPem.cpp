/// Certificate                 ::= SIGNED { SEQUENCE {
///     version                 [0] Version DEFAULT v1,
///     serialNumber                CertificateSerialNumber,
///     signature                   AlgorithmIdentifier,
///     issuer                      Name,
///     validity                    Validity,
///     subject                     Name,
///     subjectPublicKeyInfo        SubjectPublicKeyInfo,
///     issuerUniqueIdentifier  [1] IMPLICIT UniqueIdentifier OPTIONAL,
///                                 -- if present, version shall be v2 or v3
///     subjectUniqueIdentifier [2] IMPLICIT UniqueIdentifier OPTIONAL,
///                                 -- if present, version shall be v2 or v3
///     extensions              [3] Extensions OPTIONAL
///                                 -- If present, version shall be v3 -- } }
///     Version                 ::=     INTEGER { v1(0), v2(1), v3(2) }
///     CertificateSerialNumber ::=     INTEGER
/// AlgorithmIdentifier         ::=     SEQUENCE {
/// algorithm                   ALGORITHM.&id ({SupportedAlgorithms}),
/// parameters                  ALGORITHM.&Type ({SupportedAlgorithms}{ @algorithm})
/// -- Definition of the following information object set is deferred, perhaps to standardized
/// -- profiles or to protocol implementation conformance statements.
/// The set is required
/// -- specify a table constraint on the parameters component of AlgorithmIdentifier.
/// -- SupportedAlgorithms      ALGORITHM ::= { ...
/// }
/// Validity                    ::= SEQUENCE {
///     notBefore                   Time,
///     notAfter                    Time }
/// SubjectPublicKeyInfo        ::= SEQUENCE {
///     algorithm                   AlgorithmIdentifier,
///     subjectPublicKey            BIT STRING }
/// Time ::= CHOICE {
///     utcTime                     UTCTime,
///     generalizedTime             GeneralizedTime }
/// Extensions                  ::= SEQUENCE OF Extension
/// Extension                   ::= SEQUENCE {
///     extnId                      EXTENSION.&id ({ExtensionSet}),
///     critical                    BOOLEAN DEFAULT FALSE,
///     extnValue                   OCTET STRING
///                                 -- contains a DER encoding of a value of type &ExtnType
///                                 -- for the extension object identified by extnId -- }
/// ExtensionSet    EXTENSION   ::= { ...
/// }
const char rsaCertPem[] = \
"MIID1jCCAr4CCQCmD3InBVFwRjANBgkqhkiG9w0BAQUFADCBrDELMAkGA1UEBhMC"
"VVMxEzARBgNVBAgMCkNhbGlmb3JuaWExFjAUBgNVBAcMDU1pc3Npb24gVmllam8x"
"GzAZBgNVBAoMEk1lZHVzYSBEZXZlbG9wbWVudDEUMBIGA1UECwwLRW5naW5lZXJp"
"bmcxGTAXBgNVBAMMEHd3dy5tZWR1c2FkZS5vcmcxIjAgBgkqhkiG9w0BCQEWE21l"
"ZHVzYUBtZWR1c2FkZS5vcmcwHhcNMTQwNDIyMDAzMDI0WhcNMTUwNDIyMDAzMDI0"
"WjCBrDELMAkGA1UEBhMCVVMxEzARBgNVBAgMCkNhbGlmb3JuaWExFjAUBgNVBAcM"
"DU1pc3Npb24gVmllam8xGzAZBgNVBAoMEk1lZHVzYSBEZXZlbG9wbWVudDEUMBIG"
"A1UECwwLRW5naW5lZXJpbmcxGTAXBgNVBAMMEHd3dy5tZWR1c2FkZS5vcmcxIjAg"
"BgkqhkiG9w0BCQEWE21lZHVzYUBtZWR1c2FkZS5vcmcwggEiMA0GCSqGSIb3DQEB"
"AQUAA4IBDwAwggEKAoIBAQC3LzKfUI7ucOSutL9AdlgDxRx+/g/ktdBmSkf/VwdZ"
"f1fcuKh49lELnN6itsAwCAzjBmT3+IjgEqZKmTNVNHYDbMNt5+mHBNzdv0l+3BdX"
"QQ0CEpytnnsypk7yNzZ2GL/zsj6SnbJ5pPQlEZecrDaO6Uvzi6gmZ061pF+9gAuC"
"nTJyST15e1mRcyHmtoY19qUFDgxR1VN2wlpkbtcJqO8HAtta5or6EK21xQ5GU843"
"n2ArIf8VlMaUdtqanzuVISWX+7eOYcSPe1joPAYHTU6UO/flvke47vTR9Igur0ce"
"/e9yKaAArZBL618wyMRYKOV4kHFqouP6UNJOdZCs5L5XAgMBAAEwDQYJKoZIhvcN"
"AQEFBQADggEBADcmpESYiTTALeYT/T6TUs02DUhv9pwf+9em7v4hEenqUQogx5H4"
"H7dRMcq4gEz1YoyQCHemdMJDzXBhtkX6TDxHuIOTM3626/hstMIPJs3F+J/KftW0"
"KzAEtsibl20f59KwduE8+LUa9V1woBC1k1Ye/HskWGa/nl4+OBXMlOdGsKcRwTDq"
"QnpIO4tVegmUm3unjlfbqHOFYZEaN94qlq1R/wqw+0kwrGmLGg2kmiBG4WZJbmfh"
"/DecDTFK7wPwY0ny7OJMrVZJk4MTvyt1+psKlXOWMz1tRqenZtpXlxFmUQJYRzm4"
"JOfN1zE2XiEBMtN5ZCsJRCqkkcw0b32pVXc=";

