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
    ADD_NOISE       = conf["Add_Noise"]
    RETOURNEMENT    = conf["Retournement"]

    os.makedirs(REP_OUT +"/test/images", exist_ok=True)
    os.makedirs(REP_OUT +"/test/labels", exist_ok=True)
    os.makedirs(REP_OUT +"/train/images", exist_ok=True)
    os.makedirs(REP_OUT +"/train/labels", exist_ok=True)
    os.makedirs(REP_OUT +"/valid/images", exist_ok=True)
    os.makedirs(REP_OUT +"/valid/labels", exist_ok=True)


#    for lot in [ "test" ] :
    for lot in [ "test", "valid", "train" ] :


        img_File_List = [
            f for f in os.listdir(REP_IN +"/"+lot)
            if os.path.isfile(os.path.join(REP_IN +"/"+lot, f)) and f.lower().endswith(IMG_FILE_EXT)
        ]

        print(lot, "   Nombre de fichier :", len(img_File_List))
        print()


        for img_File in img_File_List:

            print("-----------------------------")
            print("\tImage :", img_File, "( ", lot, " )")

            # ---------------------------------------
            # Chargement de l'image
            image = cv2.imread( REP_IN +"/"+ lot +"/"+ img_File )
            img_hauteur, img_largeur, _ = image.shape

            print("\tSize :", img_largeur, "x", img_hauteur )

            # ---------------------------------------
            # Chargement des donnees de label et position
            #  imgData -->  [ label_id, x_center, y_center, x_box, y_box ]
            #
            imgData = get_label(conf, lot, img_File, img_largeur, img_hauteur)
            print("\timgData :", imgData)

            obj_position_x = imgData[1]
            obj_position_y = imgData[2]
            obj_size_x     = imgData[3]
            obj_size_y     = imgData[4]
 

            for i in range(ITERATION) :

                print("\t------------------------------")
                print("\tImage :", img_File, "( ", lot, " )")
                print("\titeration :", i+1, " /", ITERATION)

                # ---------------------------------------
                # nouveau format de l'image
                # ( on considère que l'image est toujours horizontale )

                # en y
                y_start = randint( 1, obj_position_y - int(obj_size_y/3) )
                y_end   = randint( obj_position_y, img_hauteur - int(obj_size_y/3) )

                # taille
                new_img_size = y_end - y_start

                # si la taille de l'immage est trop petite !
                if new_img_size < obj_size_y : 
                    new_img_size = obj_size_y
                    y_end = y_start + obj_size_y

                ratio_size_target = new_img_size / 640
   
                # en x
                #print("DEBUG :", obj_position_x, new_img_size, obj_size_x )
                x_start = randint( obj_position_x - int(new_img_size/2) , obj_position_x - int(obj_size_x/3) )
                x_end   = x_start + new_img_size
    
    
                print("\t\tnew_img_size :", new_img_size, )
                print("\t\tratio_size_target :", ratio_size_target, )
                print("\t\ty_start :", y_start, " y_end :", y_end, " x_start ", x_start, " x_end :", x_end )
    
    
                # re cadrage
                new_img = image[y_start:y_end, x_start:x_end]
                # re dimentionnement
                new_img = cv2.resize(new_img, (640,640), interpolation=cv2.INTER_AREA)
    
                # ---------------------------------------
                # recalcul des positions du label
                new_imgData = [ 0 ] *5
                new_imgData[0] = imgData[0]
                new_imgData[1] = int( (obj_position_x - x_start ) / ratio_size_target )
                new_imgData[2] = int( (obj_position_y - y_start ) / ratio_size_target )
                new_imgData[3] = int( obj_size_x / ratio_size_target )
                new_imgData[4] = int( obj_size_y / ratio_size_target )
                #print("  ", imgData)
    
   
                # --------------------------------------- 
                # Retournement de l'image
                for r in range(RETOURNEMENT+1):

                    if r > 0 : 
                        # Obtenir la matrice de rotation
                        rotation_matrix = cv2.getRotationMatrix2D((320,320), 90, 1.0)

                        # Appliquer la rotation avec la taille originale
                        new_img = cv2.warpAffine(new_img, rotation_matrix, (640,640))

                        # recalcul des positions du label
                        x_center = new_imgData[2]
                        y_center = 640 - new_imgData[1]
                        x_box    = new_imgData[4]                       # inversion des dimentions
                        y_box    = new_imgData[3]

                        new_imgData[1] = x_center
                        new_imgData[2] = y_center
                        new_imgData[3] = x_box
                        new_imgData[4] = y_box



                    # ---------------------------------------
                    # Ajout de bruit dans l'image
                    
                    new_img_noised = new_img.copy()

                    for n in range(ADD_NOISE+1) :

                        print("\t\tnoise : ", n, " /", ADD_NOISE, "   retourne : ", r, " /", RETOURNEMENT)

                        if n > 0 : add_noise(new_img_noised)

                        # --------------------------------------- 
                        # Sauvegarde
                        save_new_img(conf, lot, new_img_noised, new_imgData, img_File, i, n, r)

                        # ---------------------------------------
                        # Affichage
                        show_imgData(new_img_noised, new_imgData, screen_x, screen_y)
    
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
def save_new_img( conf, lot, img, data, img_File, i, n, r):

    file =  img_File[:-len(conf["IMG_FILE_EXT"])]

    file_img   = conf["REP_OUT"] +"/"+ lot +"/images/"+ file +"_"+ str(i) +"_n"+ str(n) +"_r"+ str(r) + conf["IMG_FILE_EXT"]
    file_label = conf["REP_OUT"] +"/"+ lot +"/labels/"+ file +"_"+ str(i) +"_n"+ str(n) +"_r"+ str(r) + conf["LABEL_FILE_EXT"]

    #print("   Sauvegarde :", file_img)
    #print("   Sauvegarde :", file_label)

    cv2.imwrite(file_img, img) 

    f = open(file_label, "w")


    # Label data
    #print("data :", data)
    label_id = data[0]
    x_center = data[1] / 640
    y_center = data[2] / 640
    x_box    = data[3] / 320
    y_box    = data[4] / 320

    txt = str(label_id) +" "+ str(x_center) +" "+ str(y_center) +" "+ str(x_box) +" "+ str(y_box) +"\n"

    f.write( txt)
    f.close()


# ----------------------------------------
def show_imgData(img, imgData, screen_x, screen_y):

    image = img.copy()

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

    cv2.imshow("image", image )        
    cv2.moveWindow("image", int((screen_x - 640)/2), int((screen_y - 640)/2))



# ----------------------------------------
def get_label(conf, lot, img, img_largeur, img_hauteur):

    label_File = img[:-len(conf["IMG_FILE_EXT"])] + conf["LABEL_FILE_EXT"]

    if os.path.isfile(conf["REP_IN"] +"/"+ lot +"/"+ label_File):
        f = open (conf["REP_IN"] +"/"+ lot +"/"+ label_File, "r")

        
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
