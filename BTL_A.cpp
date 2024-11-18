#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct SinhVien {
    string maSV;
    string hoTen;
    string gioiTinh;
    string lop;  
    float diem;  
    SinhVien* next;
    SinhVien* prev;

    SinhVien(string ma, string ht, string gt, string l, float d)
        : maSV(ma), hoTen(ht), gioiTinh(gt), lop(l), diem(d), next(nullptr), prev(nullptr) {}

    friend ostream& operator<<(ostream& os, const SinhVien& sv);
    friend istream& operator>>(istream& is, SinhVien& sv);
    friend bool operator==(const SinhVien& sv1, const SinhVien& sv2);
};

// Toán tử << để in thông tin sinh viên
ostream& operator<<(ostream& os, const SinhVien& sv) {
    os << "MSSV: " << sv.maSV << ", Ho ten: " << sv.hoTen
       << ", Gioi tinh: " << sv.gioiTinh << ", Lop: " << sv.lop
       << ", Diem: " << sv.diem;
    return os;
}

// Toán tử >> để nhập thông tin sinh viên
istream& operator>>(istream& is, SinhVien& sv) {
    cout << "Nhap ma sinh vien: ";
    getline(is, sv.maSV);
    cout << "Nhap ho ten: ";
    getline(is, sv.hoTen);
    cout << "Nhap gioi tinh: ";
    getline(is, sv.gioiTinh);
    cout << "Nhap lop: ";
    getline(is, sv.lop);
    cout << "Nhap diem: ";
    is >> sv.diem;
    is.ignore();  
    return is;
}

// Toán tử == để so sánh hai sinh viên (so sánh theo maSV)
bool operator==(const SinhVien& sv1, const SinhVien& sv2) {
    return sv1.maSV == sv2.maSV;
}

class DanhSachSinhVien {
private:
    SinhVien* head;
    SinhVien* tail;

public:
    DanhSachSinhVien() : head(nullptr), tail(nullptr) {}

    ~DanhSachSinhVien() {
        SinhVien* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Nhập thêm một sinh viên vào cuối danh sách
    void themSinhVienCuoi() {
        SinhVien* newSV = new SinhVien("", "", "", "", 0.0f);
        cin >> *newSV;  
        if (tail == nullptr) {
            head = tail = newSV;
        } else {
            tail->next = newSV;
            newSV->prev = tail;
            tail = newSV;
        }
    }

    // Nhập thông tin sinh viên cho số lượng sinh viên đã cho
    void nhapSinhVien(int n) {
        for (int i = 0; i < n; i++) {
            cout << "Nhap thong tin sinh vien thu " << i + 1 << ":" << endl;
            themSinhVienCuoi();
        }
    }

    // Hiển thị toàn bộ danh sách sinh viên
    void hienThiDanhSach() {
        if (head == nullptr) {
            cout << "Danh sach sinh vien rong!" << endl;
            return;
        }

        SinhVien* temp = head;
        while (temp != nullptr) {
            cout << *temp << endl;  
            temp = temp->next;
        }
    }

    // Xóa một sinh viên
    void xoaSinhVien(string maSV) {
        SinhVien* temp = head;
        while (temp != nullptr && temp->maSV != maSV) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Sinh vien khong ton tai!" << endl;
            return;
        }

        if (temp == head) {
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
        } else if (temp == tail) {
            tail = tail->prev;
            if (tail != nullptr) tail->next = nullptr;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Sinh vien " << maSV << " da bi xoa!" << endl;
    }

    // Sửa thông tin sinh viên
    void suaThongTinSinhVien(string maSV) {
        SinhVien* temp = head;
        while (temp != nullptr && temp->maSV != maSV) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Sinh vien khong ton tai!" << endl;
            return;
        }

        cout << "Nhap ho ten moi: ";
        getline(cin, temp->hoTen);
        cout << "Nhap gioi tinh moi: ";
        getline(cin, temp->gioiTinh);
        cout << "Nhap lop moi: ";
        getline(cin, temp->lop);
        cout << "Nhap diem moi: ";
        cin >> temp->diem;
        cin.ignore();

        cout << "Thong tin sinh vien da duoc cap nhat!" << endl;
    }

    // Tìm kiếm sinh viên theo mã SV
    void timSinhVienTheoMa(string maSV) {
        SinhVien* temp = head;
        while (temp != nullptr && temp->maSV != maSV) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Sinh vien khong ton tai!" << endl;
        } else {
            cout << "Sinh vien tim duoc: " << endl;
            cout << *temp << endl; 
        }
    }

    // Tìm sinh viên có điểm cao nhất
    void timSinhVienDiemCaoNhat() {
        if (head == nullptr) {
            cout << "Danh sach sinh vien rong!" << endl;
            return;
        }

        SinhVien* temp = head;
        SinhVien* diemCao = head;
        while (temp != nullptr) {
            if (temp->diem > diemCao->diem) {
                diemCao = temp;
            }
            temp = temp->next;
        }

        cout << "Sinh vien diem cao nhat: " << endl;
        cout << *diemCao << endl;  
    }
};

// Lớp Menu 
class Menu {
public:
    static void hienThiMenu() {
        cout << "\n======================== MENU ========================" << endl;
        cout << "1. Nhap thong tin sinh vien" << endl;
        cout << "2. Hien thi danh sach sinh vien" << endl;
        cout << "3. Xoa sinh vien" << endl;
        cout << "4. Sua thong tin sinh vien" << endl;
        cout << "5. Tim kiem sinh vien theo ma SV" << endl;
        cout << "6. Tim sinh vien diem cao nhat" << endl;
        cout << "0. Thoat" << endl;
        cout << "======================================================" << endl;
        cout << "Nhap lua chon cua ban: ";
    }

    static void xuLyMenu(DanhSachSinhVien& dssv) {
        int choice;
        string maSV;
        int soLuong;

        do {
            hienThiMenu();
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    cout << "Nhap so luong sinh vien: ";
                    cin >> soLuong;
                    cin.ignore();
                    dssv.nhapSinhVien(soLuong);
                    break;

                case 2:
                    dssv.hienThiDanhSach();
                    break;

                case 3:
                    cout << "Nhap ma sinh vien can xoa: ";
                    getline(cin, maSV);
                    dssv.xoaSinhVien(maSV);
                    break;

                case 4:
                    cout << "Nhap ma sinh vien can sua: ";
                    getline(cin, maSV);
                    dssv.suaThongTinSinhVien(maSV);
                    break;

                case 5:
                    cout << "Nhap ma sinh vien can tim: ";
                    getline(cin, maSV);
                    dssv.timSinhVienTheoMa(maSV);
                    break;

                case 6:
                    dssv.timSinhVienDiemCaoNhat();
                    break;

                case 0:
                    cout << "Thoat chuong trinh!" << endl;
                    break;

                default:
                    cout << "Lua chon khong hop le!" << endl;
                    break;
            }

        } while (choice != 0);
    }
};

int main() {
    DanhSachSinhVien dssv;
    Menu::xuLyMenu(dssv);
    return 0;
}
