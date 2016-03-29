#ifndef COATI_LICENSE_H
#define COATI_LICENSE_H

#include <memory>
#include <string>
#include <vector>

namespace Botan
{
	class RSA_PublicKey;
	class RSA_PrivateKey;
	class AutoSeeded_RNG;
}

class License
{
public:
    License();
    ~License();

    std::string getHashLine() const;
    std::string getMessage() const;
    std::string getSignature() const;
    std::string getVersionLine() const;
    std::string getOwnerLine() const;
    std::string getLicenseTypeLine() const;

    std::string getPublicKeyFilename() const;
    std::string getVersion() const;

	/// if Test License return >=0 else -1
	int getTimeLeft() const;

    void create(
			const std::string& user, const std::string& version,
			Botan::RSA_PrivateKey* privateKey, const std::string& type="Private License"
	);

    std::string getLicenseString() const;
	std::string getLicenseEncodedString(const std::string& applicationLocation) const;

    void writeToFile(const std::string& filename);
    bool load(std::istream& stream);
    bool loadFromString(const std::string& licenseText);
    bool loadFromFile(const std::string& filename);
	bool loadFromEncodedString(const std::string& encodedLicense, const std::string& applicationLocation);

	bool loadPublicKeyFromFile(const std::string&);

    bool loadPublicKeyFromString(const std::string&);
	void setVersion(const std::string&);

    bool isValid() const;
	bool isExpired() const;

    void print();

    std::string hashLocation(const std::string&);
    static bool checkLocation(const std::string&, const std::string&);

private:
	void createMessage(const std::string& user, const std::string& version, const std::string& type = 0);
	void addSignature(const std::string&);
	std::string getEncodeKey(const std::string applicationLocation) const;

	std::string m_version;
	std::string m_publicKeyFilename;
	std::shared_ptr<Botan::RSA_PublicKey> m_publicKey;
	std::vector<std::string> lines;
	std::shared_ptr<Botan::AutoSeeded_RNG> m_rng;

    const std::string KEY_FILEENDING = ".pem";
    const std::string BEGIN_LICENSE = "-----BEGIN LICENSE-----";
    const std::string END_LICENSE = "-----END LICENSE-----";
};

#endif // COATI_LICENSE_H
