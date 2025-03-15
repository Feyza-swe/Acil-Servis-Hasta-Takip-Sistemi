#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAKS 100

// Hasta bilgilerini saklayan struct
struct Hasta {
    char ad[50];
    char dogumTarihi[11]; // Ornek: "01.01.1980"
    char cinsiyet[2];     // Ornek: "E" veya "K"
    char iletisim[20];    // Ornek: "555-555-5555"
    char sikayet[100];
    int oncelik;          // 1 = Kirmizi, 2 = Sari, 3 = Yesil
    float vucutSicakligi;
    int nabiz;
    int buyukTansiyon;    // Ornek: 120
    int kucukTansiyon;    // Ornek: 80
    char receteNo[15];
};

struct Hasta kuyruk[MAKS];
int bas = -1, son = -1;

// HL7 formatinda hasta bilgilerini yazdir
void yazdirHL7(struct Hasta h) {
    printf("PID|%s|%s|%s|%s|%s|%s|%d|%.1f|%d/%d|\n",
           h.receteNo, h.ad, h.dogumTarihi, h.cinsiyet, h.iletisim, h.sikayet, 
           h.nabiz, h.vucutSicakligi, h.buyukTansiyon, h.kucukTansiyon);
}

// Recete numarasi olustur
void receteNoOlustur(char *receteNo) {
    sprintf(receteNo, "RX%05d", rand() % 100000); // RX12345 gibi
}

// Oncelik seviyesini aciklayan string dondur
const char* oncelikSeviyesi(int oncelik) {
    switch (oncelik) {
        case 1: return "Kirmizi";
        case 2: return "Sari";
        case 3: return "Yesil";
        default: return "Bilinmiyor";
    }
}

// Kuyrugu oncelik sirasina gore sirala
void kuyruguSirala() {
    for (int i = bas; i < son; i++) {
        for (int j = i + 1; j <= son; j++) {
            if (kuyruk[i].oncelik > kuyruk[j].oncelik) { // Oncelik sirasina gore
                struct Hasta gecici = kuyruk[i];
                kuyruk[i] = kuyruk[j];
                kuyruk[j] = gecici;
            }
        }
    }
}

// Yeni hasta ekle
void hastaEkle(struct Hasta h) {
    if (son == MAKS - 1) {
        printf("Kuyruk dolu! Yeni hasta eklenemiyor.\n");
        return;
    }
    if (bas == -1) bas = 0;
    son++;
    kuyruk[son] = h;
    kuyruguSirala(); // Oncelik sirasina gore sirala
    printf("Hasta eklendi: %s, Oncelik: %s, Recete No: %s\n", h.ad, oncelikSeviyesi(h.oncelik), h.receteNo);
    yazdirHL7(h); // HL7 formatinda bilgi yazdir
}

// Siradaki hastayi isle
void siradakiHastayiIsle() {
    if (bas == -1 || bas > son) {
        printf("Kuyruk bos! Islem yapilacak hasta yok.\n");
        return;
    }
    printf("Hasta isleniyor: %s\n", kuyruk[bas].ad);
    printf(" - Dogum Tarihi: %s\n", kuyruk[bas].dogumTarihi);
    printf(" - Cinsiyet: %s\n", kuyruk[bas].cinsiyet);
    printf(" - Sikayet: %s\n", kuyruk[bas].sikayet);
    printf(" - Oncelik: %s\n", oncelikSeviyesi(kuyruk[bas].oncelik));
    printf(" - Vucut Sicakligi: %.1f\n", kuyruk[bas].vucutSicakligi);
    printf(" - Nabiz: %d\n", kuyruk[bas].nabiz);
    printf(" - Tansiyon: %d/%d\n", kuyruk[bas].buyukTansiyon, kuyruk[bas].kucukTansiyon);
    printf(" - Recete No: %s\n", kuyruk[bas].receteNo);
    yazdirHL7(kuyruk[bas]); // HL7 formatinda bilgi yazdir
    bas++;
    if (bas > son) bas = son = -1; // Tum hastalar islendiyse kuyrugu sifirla
}

// Hasta listesini goruntule
void hastaListesiniGoruntule() {
    if (bas == -1 || bas > son) {
        printf("Kuyruk bos! Gosterilecek hasta yok.\n");
        return;
    }
    printf("Hastalar (Oncelik Sirasina Gore):\n");
    for (int i = bas; i <= son; i++) {
        printf("%d. %s, Oncelik: %s, Recete No: %s\n", i + 1, kuyruk[i].ad, oncelikSeviyesi(kuyruk[i].oncelik), kuyruk[i].receteNo);
    }
}

// Gecerli bir dogum tarihi al
void gecerliDogumTarihiAl(char *dogumTarihi) {
    int gun, ay, yil;
    while (1) {
        printf("Dogum tarihi (GG AA YYYY): ");
        if (scanf("%d %d %d", &gun, &ay, &yil) != 3 || gun < 1 || gun > 31 || ay < 1 || ay > 12 || yil < 1900 || yil > 2100) {
            printf("Hata: Gecersiz dogum tarihi! Ornek: 01 01 1980\n");
            while (getchar() != '\n'); // Hatali girisleri temizle
        } else {
            sprintf(dogumTarihi, "%02d.%02d.%04d", gun, ay, yil);
            break;
        }
    }
}

// Gecerli bir cinsiyet al
void gecerliCinsiyetAl(char *cinsiyet) {
    while (1) {
        printf("Cinsiyet (E/K): ");
        scanf(" %[^\n]", cinsiyet);
        if (strcmp(cinsiyet, "E") != 0 && strcmp(cinsiyet, "K") != 0) {
            printf("Hata: Gecersiz cinsiyet! E veya K giriniz.\n");
        } else {
            break;
        }
    }
}

// Gecerli bir oncelik seviyesi al
int gecerliOncelikAl() {
    int oncelik;
    while (1) {
        printf("Oncelik seviyesi (1 = Kirmizi, 2 = Sari, 3 = Yesil): ");
        if (scanf("%d", &oncelik) != 1 || oncelik < 1 || oncelik > 3) {
            printf("Hata: Gecersiz oncelik seviyesi! 1, 2 veya 3 giriniz.\n");
            while (getchar() != '\n'); // Hatali girisi temizle
        } else {
            return oncelik; // Gecerli bir deger dondur
        }
    }
}

// Gecerli bir nabiz al
int gecerliNabizAl() {
    int nabiz;
    while (1) {
        printf("Nabiz (ornek: 75): ");
        if (scanf("%d", &nabiz) != 1 || nabiz < 30 || nabiz > 200) {
            printf("Hata: Gecersiz nabiz girisi! 30 ile 200 arasinda bir deger giriniz.\n");
            while (getchar() != '\n'); // Yanlis girisleri temizle
        } else {
            return nabiz;
        }
    }
}

// Gecerli bir tansiyon al
void gecerliTansiyonAl(int *buyukTansiyon, int *kucukTansiyon) {
    while (1) {
        printf("Buyuk Tansiyon (ornek: 120): ");
        if (scanf("%d", buyukTansiyon) != 1 || *buyukTansiyon < 50 || *buyukTansiyon > 250) {
            printf("Hata: Gecersiz buyuk tansiyon degeri! 50 ile 250 arasinda bir deger giriniz.\n");
            while (getchar() != '\n'); // Yanlis girisleri temizle
            continue;
        }
        printf("Kucuk Tansiyon (ornek: 80): ");
        if (scanf("%d", kucukTansiyon) != 1 || *kucukTansiyon < 30 || *kucukTansiyon > 150) {
            printf("Hata: Gecersiz kucuk tansiyon degeri! 30 ile 150 arasinda bir deger giriniz.\n");
            while (getchar() != '\n'); // Yanlis girisleri temizle
        } else {
            break;
        }
    }
}

// Hasta bilgilerini al
void hastaBilgisiAl() {
    struct Hasta h;
    printf("Hasta adi: ");
    scanf(" %[^\n]", h.ad);
    gecerliDogumTarihiAl(h.dogumTarihi);
    gecerliCinsiyetAl(h.cinsiyet);
    printf("Iletisim bilgisi: ");
    scanf(" %[^\n]", h.iletisim);
    printf("Hasta sikayeti: ");
    scanf(" %[^\n]", h.sikayet);
    h.oncelik = gecerliOncelikAl();
    printf("Vucut sicakligi (Celsius): ");
    scanf("%f", &h.vucutSicakligi);
    h.nabiz = gecerliNabizAl();
    gecerliTansiyonAl(&h.buyukTansiyon, &h.kucukTansiyon);
    receteNoOlustur(h.receteNo);
    hastaEkle(h);
}

// Ana fonksiyon
int main() {
    int secim;
    srand(time(0)); // Rastgele recete numarasi icin

    while (1) {
        printf("\n--- Acil Servis Sistemi ---\n");
        printf("1. Yeni Hasta Ekle\n");
        printf("2. Siradaki Hastayi Isle\n");
        printf("3. Hasta Listesini Goruntule\n");
        printf("4. Cikis\n");
        printf("Secim yapiniz: ");
        if (scanf("%d", &secim) != 1) {
            printf("Hata: Gecersiz bir secim girdiniz!\n");
            while (getchar() != '\n'); // Hatali girisi temizle
            continue;
        }

        switch (secim) {
            case 1:
                hastaBilgisiAl();
                break;
            case 2:
                siradakiHastayiIsle();
                break;
            case 3:
                hastaListesiniGoruntule();
                break;
            case 4:
                printf("Sistemden cikiliyor...\n");
                return 0;
            default:
                printf("Gecersiz secim! Lutfen 1-4 arasinda bir sayi giriniz.\n");
        }
    }
}
