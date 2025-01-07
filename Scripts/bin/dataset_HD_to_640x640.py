# -----------------------------------------------------------------------------
#                           Analyse DataSet
#                                               Frederic JELMONI  - Nov2024
# -----------------------------------------------------------------------------
import os
import cv2
import json 
import numpy as np

from screeninfo import get_monitors
from random import randint

CONFIG_FILE = "dataset_HD_to_640x640.conf"

screen_x = get_monitors()[0].width
screen_y = get_monitors()[0].height

# -------------------------------------
def main():
    
    conf = get_config()

    REP_IN          = conf["REP_IN"]
    REP_OUT         = conf["REP_OUT"]
    IMG_FILE_EXT    = conf["IMG_FILE_EXT"]
    LABEL_FILE_EXT  = conf["LABEL_FILE_EXT"]
    ITERATION       = conf["Nb_Iteration_par_image"]


    img_File_List = [
        f for f in os.listdir(REP_IN)
        if os.path.isfile(os.path.join(REP_IN, f)) and f.lower().endswith(IMG_FILE_EXT)
    ]

    print("   Nombre de fichier :", len(img_File_List))
    print()


    for img_File in img_File_List:

     for i in range(ITERATION) :

        print("-----------------------------")
        print("   Image :", img_File)


        # ---------------------------------------
        # Chargement de l'image
        image = cv2.imread( REP_IN +"/"+ img_File )
        img_hauteur, img_largeur, _ = image.shape

        print("   Size :", img_largeur, "x", img_hauteur )

        # ---------------------------------------
        # Chargement des donnees de label et position
        #  imgData -->  [ label_id, x_center, y_center, x_box, y_box ]
        #
        imgData = get_label(conf, img_File, img_largeur, img_hauteur)
        print("  ", imgData)


        # ---------------------------------------
        # recadrage de l'image
        x_offset  = randint(-50, 50) * 4
        y_offset  = randint(-50, 50) * 4

        x_start = imgData[1] - 320 + x_offset
        y_start = imgData[2] - 320 + y_offset
        x_end   = x_start + 640
        y_end   = y_start + 640

        new_img = image[y_start:y_end, x_start:x_end]

        # ---------------------------------------
        # recalcul des positions du label
        imgData[1] = 320 - x_offset
        imgData[2] = 320 - y_offset
        print("  ", imgData)

        # ---------------------------------------
        # Ajout de bruit dans l'image
        add_noise(new_img)

        # ---------------------------------------
        # Sauvegarde
        save_new_img(conf, new_img, imgData, img_File, i)


        # ---------------------------------------
        # Affichage
        show_imgData(new_img, imgData)
        cv2.imshow("image", new_img )        
        cv2.moveWindow("image", int((screen_x - 640)/2), int((screen_y - 640)/2))

        # ---------------------------------------
        # Gestion du clavier
        key = cv2.waitKey(1) & 0xFF

        if key == 27:                               exit()

        
    cv2.destroyAllWindows()

    print()
    print()

# ----------------------------------------
def add_noise(img, seuil=2):

    rand_val = np.random.normal(0, 1, (640,640))    

    img[ rand_val > seuil ] = 0
    img[ rand_val < -seuil ] = 255


# ----------------------------------------
def save_new_img( conf, img, data, img_File, i):

    file =  img_File[:-len(conf["IMG_FILE_EXT"])]

    file_img   = conf["REP_OUT"] +"/"+ file +"_"+ str(i) + conf["IMG_FILE_EXT"]
    file_label = conf["REP_OUT"] +"/"+ file +"_"+ str(i) + conf["LABEL_FILE_EXT"]

    print("   Sauvegarde :", file_img)
    print("   Sauvegarde :", file_label)

    cv2.imwrite(file_img, img) 

    f = open(file_label, "w")


    # Label data
    print("data :", data)
    label_id = data[0]
    x_center = data[1] / 640
    y_center = data[2] / 640
    x_box    = data[3] / 320
    y_box    = data[4] / 320

    txt = str(label_id) +" "+ str(x_center) +" "+ str(y_center) +" "+ str(x_box) +" "+ str(y_box) +"\n"

    f.write( txt)
    f.close()


# ----------------------------------------
def show_imgData(image, imgData):

    label_id = imgData[0]
    x_center = imgData[1]
    y_center = imgData[2]
    x_box    = imgData[3]
    y_box    = imgData[4]

    x1 = x_center - x_box
    x2 = x_center + x_box
    y1 = y_center - y_box
    y2 = y_center + y_box

    # Affichage du point central
    cv2.circle(image, (x_center, y_center), 5, (0,0,255), -1)

    # Afficher les lignes
    cv2.line(image, (x1, y1), (x2, y1), (0,0,255), 2)
    cv2.line(image, (x1, y2), (x2, y2), (0,0,255), 2)
    cv2.line(image, (x1, y1), (x1, y2), (0,0,255), 2)
    cv2.line(image, (x2, y1), (x2, y2), (0,0,255), 2)


# ----------------------------------------
def get_label(conf, img, img_largeur, img_hauteur):

    label_File = img[:-len(conf["IMG_FILE_EXT"])] + conf["LABEL_FILE_EXT"]

    if os.path.isfile(conf["REP_IN"] +"/"+ label_File):
        f = open (conf["REP_IN"] +"/"+ label_File, "r")

        
        # pour chaque label
        for line in f: 
            #print("   ", line, end="")
                
            data = line.split(" ")

            label_id = int(data[0])
            x_center = int(float(data[1]) * img_largeur)
            y_center = int(float(data[2]) * img_hauteur)
            x_box    = int(float(data[3]) * img_largeur /2)
            y_box    = int(float(data[4]) * img_hauteur /2)

           
        return [ label_id, x_center, y_center, x_box, y_box ]

    return None



# ----------------------------------------
def get_config(default = False):

    file = None

    if default == False :

        try:
            file = open(CONFIG_FILE, "r")
        except Exception as e :
            print("Err :", e)


    if file :
        conf = json.load(file)
        file.close
    else :  
        print("Config Error !!! ")
        exit()

    return conf

# ----------------------------------------
def show_help():

    print("\n\n\n")

    print("---------------------------------------------------")
    print("   fleches droite/gauche pour changer d'image ")
    print("   'espace'  pour faire defiler ")
    print("---------------------------------------------------")
    print("\n\n\n")



# -------------------------------------
if __name__ == "__main__" :
    main()
