# 🏥 Acil Servis Hasta Takip Sistemi (ER Patient Tracking System)

Bu proje, hastanelerin acil servis bölümlerinde hasta kayıtlarını yönetmek, tıbbi öncelik (Triage) kurallarına göre hastaları sıralamak ve sağlık bilişimi standartlarından biri olan **HL7 formatında** çıktı üretmek amacıyla C dili ile geliştirilmiştir.

## 🚀 Projenin Amacı
Acil servis ortamındaki yoğunluğu yönetmek için hastaları tıbbi aciliyetlerine göre (Kırmızı, Sarı, Yeşil alan) otomatik olarak sıralayan ve her hastaya benzersiz bir reçete/takip numarası atayan bir simülasyon sağlamaktır.

## ✨ Özellikler
- **Triage (Öncelik) Yönetimi:** Hastalar öncelik seviyelerine göre (1: En yüksek, 3: En düşük) kuyrukta otomatik olarak sıralanır.
- **HL7 Standardına Uygun Çıktı:** Hasta bilgileri, HL7 PID (Patient Identification) segmenti formatında dışa aktarılabilir.
- **Veri Doğrulama:** Doğum tarihi, nabız, ateş ve tansiyon gibi kritik veriler için giriş kontrolleri.
- **Benzersiz ID Üretimi:** Her hasta için rastgele `RX00000` formatında reçete numarası oluşturma.
- **Dinamik Kuyruk Yönetimi:** Hastaların işlenmesi (muayene edilmesi) ve listeden çıkarılması.

## 🛠️ Kullanılan Teknolojiler
- **Programlama Dili:** C (C99/C11 Standartları)
- **Veri Yapıları:** Yapılar (Structs), Öncelikli Kuyruk (Priority Queue) Mantığı.
- **Algoritmalar:** Kabarcık Sıralaması (Bubble Sort) ile öncelik bazlı dinamik sıralama.
- **Kütüphaneler:** `stdio.h`, `stdlib.h`, `string.h`, `time.h`.

## 📦 Kurulum ve Çalıştırma

### Gereksinimler
- GCC veya benzeri bir C derleyicisi.

### Derleme
Terminal veya komut istemcisini açarak aşağıdaki komutu çalıştırın:
```bash
gcc -o acil_servis acil_servis.c
```

### Çalıştırma
```bash
./acil_servis
```

## 📋 Kullanım Kılavuzu
Program açıldığında karşınıza çıkan menüden aşağıdaki işlemleri yapabilirsiniz:
1.  **Yeni Hasta Ekle:** Hastanın kişisel bilgilerini ve vital bulgularını (nabız, tansiyon vb.) girin.
2.  **Sıradaki Hastayı İşle:** Kuyruktaki en yüksek öncelikli (Kırmızı alan) hastayı muayeneye alır ve bilgilerini görüntüler.
3.  **Hasta Listesini Görüntüle:** Bekleyen tüm hastaları tıbbi öncelik sırasına göre listeler.
4.  **Çıkış:** Programı sonlandırır.

## 🧬 HL7 Veri Formatı
Sistem, sağlık sistemleri arası entegrasyonu simüle etmek için her kayıtta şu formatı kullanır:
`PID|<Reçete No>|<Ad>|<Doğum Tarihi>|<Cinsiyet>|<İletişim>|<Şikayet>|<Nabız>|<Vücut Sıcaklığı>|<Tansiyon>|`

**Örnek Çıktı:**
```text
PID|RX84201|Ayşe Yılmaz|22.10.1990|K|555-123-4567|Göğüs Ağrısı|110|37.2|140/90|
```

## 🚥 Öncelik Seviyeleri
| Seviye | Renk | Açıklama |
| :--- | :--- | :--- |
| **1** | 🔴 Kırmızı | Hayati tehlike, anında müdahale. |
| **2** | 🟡 Sarı | Ciddi durum, gözlem altında bekleyebilir. |
| **3** | 🟢 Yeşil | Hafif yaralanma veya genel şikayet. |

---

### 📄 Lisans
Bu proje MIT lisansı altında sunulmaktadır. Eğitim ve geliştirme amaçlı özgürce kullanılabilir.
