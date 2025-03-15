# Acil Servis Hasta Takip Sistemi

Bu proje, hastaların bilgilerini yönetmek, öncelik sırasına göre işlem yapmak ve HL7 formatında çıktı almak için geliştirilmiş bir sistemdir. Sistem, acil servis ortamlarında hasta işlemlerini kolaylaştırmayı hedefler.

## Özellikler
- Yeni hasta ekleme ve öncelik sırasına göre kuyruğa dahil etme
- HL7 formatında hasta bilgisi çıktısı sağlama
- Hastaları öncelik sırasına göre işleme
- Hasta listesini görüntüleme

## Kullanılan Teknolojiler
- **C Programlama Dili:** Sistemin temelini oluşturan programlama dili.
- **Yapılar (Structs):** Hasta bilgilerinin yönetiminde kullanıldı.
- **Rastgele Sayılar (Random):** Reçete numaralarının oluşturulmasında kullanıldı.
- **Kuyruk Yapısı (Queue):** Hastaların öncelik sırasına göre yönetimi sağlandı.

## Kurulum ve Kullanım

### Derleme ve Çalıştırma
1. Kodları derlemek için terminal üzerinde aşağıdaki komutları kullanın:
   ```bash
   gcc -o acil_servis acil_servis.c

2. Derlemenin ardından programı çalıştırmak için:
./acil_servis


## Menü Seçenekleri
Program çalıştırıldığında, aşağıdaki seçeneklerden biri seçilebilir:

1. Yeni Hasta Ekle: Hasta bilgilerini girmek ve kuyruğa eklemek için.
2. Sıradaki Hastayı İşle: Öncelikli hastayı işleyip listeden çıkarmak için.
3. Hasta Listesini Görüntüle: Mevcut hasta listesini öncelik sırasına göre görüntülemek için.
4. Çıkış: Programı sonlandırmak için.

## HL7 Formatı
Hasta bilgileri HL7 formatında aşağıdaki gibi görüntülenir:
   ```bash
PID|<Reçete No>|<Ad>|<Doğum Tarihi>|<Cinsiyet>|<İletişim>|<Şikayet>|<Nabız>|<Vücut Sıcaklığı>|<Tansiyon (Büyük/Küçük)>|
```
## Örnek Çıktı
   ```bash
PID|RX12345|Ahmet Yilmaz|15.03.1985|E|555-555-5555|Baş ağrısı|80|36.5|130/85|
```
