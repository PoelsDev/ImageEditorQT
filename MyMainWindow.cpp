#include <iostream>
#include <cmath>
#include <QFileDialog>
#include <QtGui/QtGui>
#include "MyMainWindow.h"
#include <QRectF>
using namespace std;

//make window: initialize different components: m_label_picture contains image
MyMainWindow::MyMainWindow(QWidget *parent){
    //create picture
    m_label_picture = new QLabel();
    QPixmap qp = QPixmap(m_image_path.c_str());
    m_label_picture->setPixmap(qp);
    m_label_picture->resize(610,384);
    m_label_kernelInput = new QLabel("Kernel Input:");
    m_label_savedKernels = new QLabel("Save Kernels:");
    m_label_contrast = new QLabel("Contrast:");
    m_label_brightness = new QLabel("Brightness:");
    m_label_customProgram = new QLabel("Custom Program:");
    // Output image for multiple filters
    QImage img(m_image_path.c_str());
    m_outputImage = QImage(img);
    //create button
    m_button_open = new QPushButton("Open");
    m_button_grey = new QPushButton("Grey");
    m_button_blur = new QPushButton("Blur");
    m_button_edge = new QPushButton("Edge");
    m_button_runCustomProgram = new QPushButton("Run Custom Program");
    m_button_applyKernel = new QPushButton("Apply Kernel");
    m_button_saveKernel = new QPushButton("Save Kernel");
    m_button_runKernel = new QPushButton("Run Kernel");
    //Text input
    m_text_Input = new QTextEdit();
    m_text_ProgramInput = new QTextEdit();
    m_save_name = new QLineEdit("Example-name-3x3");
    //ComboBox
    m_combobox_kernels = new QComboBox();
    //CheckBox
    m_checkbox = new QCheckBox("Multiple filters");
    //create spinner
    //Contrast
    m_slider_Contrast = new QSlider(Qt::Horizontal);
    m_slider_Contrast->setFocusPolicy(Qt::StrongFocus);
    m_slider_Contrast->setTickPosition(QSlider::TicksBothSides);
    m_slider_Contrast->setTickInterval(50);
    m_slider_Contrast->setSingleStep(10);
    m_slider_Contrast->setRange(-128,128);
    //Brightness
    m_slider_Brightness = new QSlider(Qt::Horizontal);
    m_slider_Brightness->setFocusPolicy(Qt::StrongFocus);
    m_slider_Brightness->setTickPosition(QSlider::TicksBothSides);
    m_slider_Brightness->setTickInterval(50);
    m_slider_Brightness->setSingleStep(10);
    m_slider_Brightness->setRange(-255,255);
    //add to window using Box layout
    m_layout= new QGridLayout;  /// Voor extra mogelijkheden qua uiterlijk heb ik de layout naar "grid" veranderd om het programma gebruiksvriendelijker te maken
    m_layout->addWidget(m_label_picture);
    m_layout->addWidget(m_button_open, 1, 1); /// Met de gridlayout kan ik posities aan objecten meegeven
    m_layout->addWidget(m_button_grey,2,1);
    m_layout->addWidget(m_button_blur,3,1);
    m_layout->addWidget(m_button_edge,4,1);
    m_layout->addWidget(m_button_runCustomProgram, 14, 1);
    m_layout->addWidget(m_label_contrast, 1, 0);
    m_layout->addWidget(m_slider_Contrast, 2, 0);
    m_layout->addWidget(m_label_brightness, 3, 0);
    m_layout->addWidget(m_slider_Brightness,4,0);
    m_layout->addWidget(m_label_kernelInput,5,0);
    m_layout->addWidget(m_text_Input,6,0);
    m_layout->addWidget(m_button_applyKernel, 6, 1);
    m_layout->addWidget(m_save_name, 11, 0);
    m_layout->addWidget(m_button_saveKernel, 11, 1);
    m_layout->addWidget(m_label_savedKernels,10,0);
    m_layout->addWidget(m_combobox_kernels, 12, 0);
    m_layout->addWidget(m_button_runKernel, 12, 1);
    m_layout->addWidget(m_checkbox,0,1);
    m_layout->addWidget(m_text_ProgramInput, 14, 0);
    m_layout->addWidget(m_label_customProgram, 13, 0);
    this->setLayout(m_layout);
    //set-up event handling, this couples 'click'/'slide' (== component signal) to a method that is triggered on the event
    connect(m_button_open, SIGNAL (released()), this, SLOT (clickOpenFile()));
    connect(m_button_grey, SIGNAL (released()), this, SLOT (clickButtonGrey()));
    connect(m_button_blur, SIGNAL (released()), this, SLOT (clickButtonBlur()));
    connect(m_button_edge, SIGNAL (released()), this, SLOT (clickButtonEdge()));
    connect(m_checkbox, SIGNAL (stateChanged(int)), this, SLOT (resetSavedOutputImage()));
    connect(m_button_saveKernel, SIGNAL (released()), this, SLOT (saveCustomKernel()));
    connect(m_button_runKernel, SIGNAL (released()), this, SLOT (runCustomKernel()));
    connect(m_button_applyKernel, SIGNAL (released()), this, SLOT (applyCustomKernel()));
    connect(m_button_runCustomProgram, SIGNAL (released()), this, SLOT (runCustomProgram()));
    connect(m_slider_Contrast, SIGNAL(valueChanged(int)), this, SLOT(setValueContrast(int)));
    connect(m_slider_Brightness, SIGNAL(valueChanged(int)), this, SLOT(setValueBrightness(int)));
   }

void MyMainWindow::clickOpenFile(){
    this->m_image_path = QFileDialog::getOpenFileName(this, "Open Image", "~", "Image Files (*.png *.jpg *.bmp)").toStdString();
    QImage img(m_image_path.c_str());
    m_label_picture->setPixmap(QPixmap::fromImage(img));
}

void MyMainWindow::clickButtonGrey(){
    cout << "clickButtonGrey" << endl;
    QImage img = this->getImageToEdit();
    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            QColor c =  QColor(img.pixel(x,y));
            int grey  = (c.red() + c.green() + c.blue())/3;
            c.setRed(grey);
            c.setGreen(grey);
            c.setBlue(grey);
            img.setPixel(x,y,c.rgb());
        }
    }
    this->setKernel(img);
}

void MyMainWindow::setValueContrast(int contrast){
    QImage img = this->getImageToEdit();
    double contrast_change = (259 * (double(contrast) + 255)) / (255 * (259 - double(contrast))); /// Ik bereken het contrast en itereer over elke pixel om het er op toe te passen.
    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            QColor c = QColor(img.pixel(x, y));
            c.setRed(clamp((int) (contrast_change * (c.red() - 128) + 128))); /// Dit doe ik voor alle RGB waarde.
            c.setGreen(clamp((int) (contrast_change * (c.green() - 128) + 128)));
            c.setBlue(clamp((int) (contrast_change * (c.blue() - 128) + 128)));
            img.setPixel(x, y, c.rgb());
        }
    }
    this->setKernel(img);
    cout << "Contrast=" << contrast << endl;
}

void MyMainWindow::setValueBrightness(int b) {
    QImage img = this->getImageToEdit(); /// Dit is gelijkaardig aan de vorige functie maar hierbij neem ik dan de gepaste brightness formule.
    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            QColor c = QColor(img.pixel(x, y));
            c.setRed(clamp(c.red() + b));
            c.setGreen(clamp(c.green() + b));
            c.setBlue(clamp(c.blue() + b));
            img.setPixel(x, y, c.rgb());
        }
    }
    this->setKernel(img);
    cout << "Brightness=" << b << endl;
}

void MyMainWindow::clickButtonBlur() {
    QImage img = this->getImageToEdit(); /// Deze event handler doet weinig tot niets, het geeft aan de "createKernel()" functie de kernel en image mee, zowel als of de size gebruikt wordt om de waardes te normalizeren.
    vector<vector<float>> blurKernel = {{1,1,1},{1,1,1},{1,1,1}};
    QImage outImage = this->createKernel(blurKernel, img, true);
    this->setKernel(outImage);
}

void MyMainWindow::clickButtonEdge() {
    QImage img = this->getImageToEdit();
    QImage outImage = QImage(img);

    vector<int> rgba1;
    vector<int> rgba2;
    /// In deze functie itereer ik over elke pixel en zoek ik hun nieuwe waarde voor zowel de Kx kernel als Ky kernel.
    vector<vector<float>> XKernel = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    vector<vector<float>> YKernel = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    float total = 0;
    int grayTotal;
    for (int y = 1; y < img.height()-1; y++) { /// omdat we met kernels werken vermijdt ik de rand door te itereren over de binneste pixels (rand ontweken).
        for (int x = 1; x < img.width()-1; x++) {
            rgba1 = this->createNewPixel(XKernel, img, x, y); /// ik maak nieuwe pixels
            rgba2 = this->createNewPixel(YKernel, img, x, y);
            total = pow(rgba1[3], 2.0)+pow(rgba2[3],2.0); /// ik pas de formule toe
            grayTotal = clamp((int)sqrt(total));

            QColor pixelColor;
            pixelColor.setRed(grayTotal); /// ik pas de nieuwe pixels toe op de afbeelding.
            pixelColor.setGreen(grayTotal);
            pixelColor.setBlue(grayTotal);
            outImage.setPixel(x, y, pixelColor.rgb());
        }
    }

    this->setKernel(outImage);
}

void MyMainWindow::applyCustomKernel() { /// Dit is de eventhandler voor de custom kernel. Het principe is hetzelfde als dat van de vorige kernelfilters, alleen ga ik hier eerst de kernel uit de input halen.
    QImage img = this->getImageToEdit();
    vector<vector<float>> kernel = this->getTextInputKernel(); /// ik neem de kernel uit de input
    QImage outImage = this->createKernel(kernel, img, false); /// ik maak de kernel
    this->setKernel(outImage); /// ik verander de image
}


void MyMainWindow::saveCustomKernel() {
    QString kernelName = m_save_name->text(); /// In deze eventhandler voeg ik de custom kernel toe aan de combobox en sla ik hem op in een map genaamt m_savedKernels
    string kernelNameAsString = kernelName.toUtf8().constData();
    if(!kernelNameAsString.empty()){
        m_savedKernels[kernelNameAsString] = this->getTextInputKernel(); /// ik sla hem op in de map
        m_combobox_kernels->addItem(kernelName); /// ik voeg hem toe aan de combobox
    }
}

void MyMainWindow::runCustomKernel() {
    QImage img = this->getImageToEdit(); /// Deze eventhandler runt een kernel die is geselecteerd in de combobox
    QString input = m_combobox_kernels->currentText(); /// ik haal de input uit de combobox
    string inputAsString = input.toUtf8().constData();
    vector<vector<float>> kernel = m_savedKernels[inputAsString]; /// ik vraag de juiste kernel op.
    QImage outImage = this->createKernel(kernel, img, false); /// ik maak de nieuwe image en toon het
    this->setKernel(outImage);
}

void MyMainWindow::runCustomProgram() { /// Deze eventhandler laat je toe om een custom program uit te voeren
    QString input = m_text_ProgramInput->toPlainText();
    string inputAsString = input.toUtf8().constData(); /// ik haal de input uit de custom program textedit

    m_checkbox->setChecked(true); /// Ik gebruik een checkbox die ervoor zorgt dat meerdere filters tegelijkertijd worden toegepast. In deze eventhandler zet ik deze standaard op "Checked".

    vector<string> commands = this->parseString(inputAsString, "\n"); /// ik parse de commands

    for(auto s: commands){
        if(s.find("contrast") != string::npos){ /// ik splits de commands op in gevallen en gebruik voor het grootste deel eventhandlers om de commands uit te voeren, bv: setBrightness
            vector<string> contrast_input = this->parseString(s, "(");
            vector<string> valueAsString = this->parseString(contrast_input[1], ")");
            int value = stoi(valueAsString[0]);
            this->setContrast(value);
        } else if (s.find("brightness") != string::npos){
            vector<string> brightness_input = this->parseString(s, "(");
            vector<string> valueAsString = this->parseString(brightness_input[1], ")");
            int value = stoi(valueAsString[0]);
            this->setBrightness(value);
        } else if (s.find("kernel") != string::npos){
            QImage img = this->getImageToEdit();
            vector<string> kernel_input = this->parseString(s, "(");
            vector<string> kernelAsString1 = this->parseString(kernel_input[1], ")");
            vector<string> kernelAsString2 =this->parseString(kernelAsString1[0], ";");
            vector<vector<string>> kernelValuesAsStrings;
            vector<vector<float>> kernel;

            for(auto s: kernelAsString2){
                kernelValuesAsStrings.push_back(this->parseString(s,","));
            }

            kernel = this->toKernel(kernelValuesAsStrings);
            QImage outImage = this->createKernel(kernel, img, false);
            this->setKernel(outImage);
        } else if(s.find("sobel()") != string::npos){
            this->clickButtonEdge();
        }
    }
}

void MyMainWindow::resetSavedOutputImage() { ///Eventhandler: Reset de image als de waarde van de checkbox (multiple filters) wordt aangepast. (Dit vermijdt dat na enkele malen aanpassen van de checkbox je enkel zwarte of witte output krijgt.)
    QImage img(m_image_path.c_str());
    m_outputImage = QImage(img);
}

///////////////////////// EXTRA FUNCTIONS ////////////////////////

QImage MyMainWindow::createKernel(vector<vector<float>>& kernelMatrix, QImage &image, bool withSize) { /// deze itereert over alle pixels van de image en past de kernel er op toe.
    QImage outImage = QImage(image);

    int kernel_W = kernelMatrix[0].size(); /// kernel width & height als deze gevraagd zijn
    int kernel_H = kernelMatrix.size();

    for (int y = 1; y < image.height()-1; y++) {
        for (int x = 1; x < image.width()-1; x++) {
            QColor out;
            vector<int> rgba = this->createNewPixel(kernelMatrix, image, x, y); /// een nieuwe pixel wordt gemaakt met de kernel die is meegegeven

            if(withSize){
                rgba[0] = rgba[0]/(kernel_W * kernel_H);
                rgba[1] = rgba[1]/(kernel_W * kernel_H);
                rgba[2] = rgba[2]/(kernel_W * kernel_H);
            }

            out.setRed(clamp(rgba[0]));
            out.setGreen(clamp(rgba[1]));
            out.setBlue(clamp(rgba[2]));

            outImage.setPixel(x, y, out.rgb());
        }
    }

    return outImage; /// een nieuwe afbeelding wordt teruggegeven.
}

void MyMainWindow::setKernel(QImage& img) { /// Deze functie gaat kijken of er meerdere filters moeten worden toegepast en gaat daarna de image (parameter) displayen.
    if(m_checkbox->checkState() == 0){
        m_label_picture->setPixmap(QPixmap::fromImage(img));
    } else if (m_checkbox->checkState() == 2){
        m_outputImage = img;
        m_label_picture->setPixmap(QPixmap::fromImage(img));
    }

}

vector<int> MyMainWindow::createNewPixel(vector<vector<float>>& kernelMatrix, QImage& image, int x, int y) { /// deze functie krijgt een pixel coordinaat mee en past de kernel er op toe.
    QColor in;

    int redPixel = 0;
    int greenPixel = 0;
    int bluePixel = 0;
    int grayScalePixel = 0;

    int kernelIndexY = 0;
    for (int j = y - 1; j <= y + 1; j++) { /// er wordt geïtereerd over de kernel en er worden nieuwe RGB(Gray) waardes berekend.
        int kernelIndexX = 0;
        for (int i = x - 1; i <= x + 1; i++) {

            in = QColor(image.pixel(i,j));

            redPixel += in.red() * kernelMatrix[kernelIndexY][kernelIndexX];
            greenPixel += in.green() * kernelMatrix[kernelIndexY][kernelIndexX];
            bluePixel += in.blue() * kernelMatrix[kernelIndexY][kernelIndexX];

            grayScalePixel += this->getGrayscale(in)*kernelMatrix[kernelIndexY][kernelIndexX];

            kernelIndexX++;
        }
        kernelIndexY++;
    }

    return {redPixel, greenPixel, bluePixel, grayScalePixel}; /// de nieuwe RGB(Gray) waardes teruggegeven.
}

float MyMainWindow::getGrayscale(QColor c) { /// Deze functie krijgt een kleur mee en geeft van deze kleur de grayscale terug.
    return ((c.red() + c.green() + c.blue())/3);
}

vector<string> MyMainWindow::parseString(string input, string delimiter) { /// deze functie krijgt een string mee en een delimiter en gaat deze string parsen en teruggeven als vector van strings
    size_t pos = 0;
    string parsedString;
    vector<string> output;
    while ((pos = input.find(delimiter)) != string::npos) {
        parsedString = input.substr(0, pos);
        input.erase(0, pos + delimiter.length());
        output.push_back(parsedString);
    }
    output.push_back(input);
    return output;
}

vector<vector<float>> MyMainWindow::toKernel(vector<vector<string>> kernelStrings) { /// Deze functie krijgt een vector van vector van strings (kernel value als strings) en zet deze om in een bruikbare kernel
    vector<vector<float>> output;
    for(auto v: kernelStrings){ /// er wordt geïtereerd over de kernel van strings en deze wordt dan omgezet in een kernel van floats.
        vector<float> temp;
        for(auto value: v){
            int intValue = stoi(value);
            temp.push_back((float)intValue);
        }
        output.push_back(temp);
        temp.clear();
    }

    return output; /// de kernel wordt terug gegeven.
}

int MyMainWindow::clamp(int color) { /// clamp zal op basis van een int kijken of deze groter is als 0 (zo niet geeft deze 0) of kleiner dan 255 (zo niet geeft deze 255).
    if(0<=color && color<=255){
        return color;
    } else if (color<0) {
        return 0;
    } else if (color > 255){
        return 255;
    }
}

vector<vector<float>> MyMainWindow::getTextInputKernel() { /// deze functie wordt gebruikt bij de customkernel eventhandler om de input van het textedit object naar een bruikbare kernel om te zetten.
    QString input = m_text_Input->toPlainText();
    string inputAsString = input.toUtf8().constData();

    vector<string> temp_strings1 = this->parseString(inputAsString, ";"); /// de input wordt geparsed
    vector<vector<string>> temp_strings2;
    vector<vector<float>> kernel;

    for(auto s: temp_strings1){
        temp_strings2.push_back(this->parseString(s,",")); /// de input wordt nog 1 maal geparsed om de weldegelijke values als strings te krijgen.
    }

    kernel = toKernel(temp_strings2); /// de string values worden omgezet naar float values

    return kernel; /// een bruikbare kernel wordt teruggegeven
}

QImage MyMainWindow::getImageToEdit() { /// Deze functe gaat bepalen of er wordt gewerkt met de image waarop meerdere filters kan worden toegepast of niet.
    QImage img(m_image_path.c_str());
    if (m_checkbox->checkState() == 0){
        return img;
    } else if(m_checkbox->checkState() == 2){
        return m_outputImage;
    }
}

void MyMainWindow::setBrightness(int value) { /// Zet de brightness op een bepaalde waarde "value"
    if (value >= -128 && value <= 128){
        m_slider_Brightness->setValue(value);
    }
}

void MyMainWindow::setContrast(int value) { /// Zet het contrast op een bepaalde waarde "value"
    if(value >=-255 && value <= 255){
        m_slider_Contrast->setValue(value);
    }
}




