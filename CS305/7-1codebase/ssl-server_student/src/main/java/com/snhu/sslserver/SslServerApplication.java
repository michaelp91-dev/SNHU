package com.snhu.sslserver;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

// Import for cryptographic hashing
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Base64; // For Base64 encoding the hash for display

@SpringBootApplication
public class SslServerApplication {

    public static void main(String[] args) {
        SpringApplication.run(SslServerApplication.class, args);
    }

}

@RestController
class SslServerController {

    @RequestMapping("/hash")
    public String myHash() {
        String uniqueData = "Michael Puckett"; // Your unique data string with your name

        String hashAlgorithm = "SHA-256";
        String encryptionCipher = "AES-256"; 

        String checksum = "";
        try {
            MessageDigest digest = MessageDigest.getInstance(hashAlgorithm);
            byte[] hashedBytes = digest.digest(uniqueData.getBytes());
            checksum = Base64.getEncoder().encodeToString(hashedBytes);

        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            checksum = "Error: " + hashAlgorithm + " algorithm not found.";
        }

        return "<p>Unique Data String: " + uniqueData + "</p>" +
               "<p>Checksum Algorithm: " + hashAlgorithm + "</p>" +
               "<p>Associated Encryption Cipher for Application: " + encryptionCipher + "</p>" +
               "<p>Checksum Hash Value: " + checksum + "</p>";
    }
}
