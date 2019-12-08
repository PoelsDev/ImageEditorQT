#ifndef IMAGEEDITOR_MYMAINWINDOW_H
#define IMAGEEDITOR_MYMAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QtWidgets/QTextEdit>
#include <qlineedit.h>
#include <qcombobox.h>
#include <map>
#include <qcheckbox.h>

using namespace std;

class MyMainWindow : public QWidget
{
    Q_OBJECT //macro: ignore this special syntax
public:
    MyMainWindow(QWidget *parent = 0);
private slots:
    //event handlers:
    void clickOpenFile();
    void clickButtonGrey();
    void clickButtonBlur();
    void clickButtonEdge();
    void setValueContrast(int contrast);
    void setValueBrightness(int b);
    void applyCustomKernel();
    void saveCustomKernel();
    void runCustomKernel();
    void runCustomProgram();
    void resetSavedOutputImage();
private:
    float getGrayscale(QColor c);
    int clamp(int color);
    QImage createKernel(vector<vector<float>>& kernelMatrix, QImage& image, bool withSize);
    void setKernel(QImage& img);
    vector<int> createNewPixel(vector<vector<float>>& kernelMatrix, QImage& image, int x, int y);
    vector<string> parseString(string input, string delimiter);
    vector<vector<float>> toKernel(vector<vector<string>> kernelStrings);
    vector<vector<float>> getTextInputKernel();
    QImage getImageToEdit();
    void setBrightness(int value);
    void setContrast(int value);
private:
    //Buttons
    QPushButton* m_button_open;
    QPushButton* m_button_grey;
    QPushButton* m_button_blur;
    QPushButton* m_button_edge;
    QPushButton* m_button_applyKernel;
    QPushButton* m_button_saveKernel;
    QPushButton* m_button_runKernel;
    QPushButton* m_button_runCustomProgram;
    //Sliders
    QSlider* m_slider_Contrast;
    QSlider* m_slider_Brightness;
    //Other
    QTextEdit* m_text_Input;
    QTextEdit* m_text_ProgramInput;
    QLineEdit* m_save_name;
    QComboBox* m_combobox_kernels;
    QLabel* m_label_picture;
    QLabel* m_label_kernelInput;
    QLabel* m_label_savedKernels;
    QLabel* m_label_contrast;
    QLabel* m_label_brightness;
    QLabel* m_label_customProgram;
    QGridLayout* m_layout;
    string m_image_path = "../steam.png";
    map<string,vector<vector<float>>> m_savedKernels;
    QCheckBox* m_checkbox;
    QImage m_outputImage;
};


#endif //IMAGEEDITOR_MYMAINWINDOW_H
