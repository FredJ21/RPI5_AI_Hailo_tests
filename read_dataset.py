#!/usr/bin/python
# -----------------------------------------------------------------------------
#                           Analyse DataSet
#                                               Frederic JELMONI  - Nov2024
# -----------------------------------------------------------------------------
import os
import cv2
import json 

from screeninfo import get_monitors

CONFIG_FILE = "read_dataset.conf"



font = cv2.FONT_HERSHEY_SIMPLEX  # Police d'écriture
taille = 0.8  # Taille de la police
col_blanc  = (255, 255, 255)  # Couleur du texte (blanc en RGB)
col_noir   = (0, 0, 0)  
col_rouge  = (0, 0, 255)  
epaisseur  = 1 # Épaisseur du texte
position_x = 10
position_y = 30

screen_x = get_monitors()[0].width
screen_y = get_monitors()[0].height


# -------------------------------------
def main():
    
    conf = get_config()

    REP             = conf["REP"]
    REP_images      = REP + conf["REP_images"]
    REP_labels      = REP + conf["REP_labels"]
    IMG_FILE_EXT    = conf["IMG_FILE_EXT"]
    LABEL_FILE_EXT  = conf["LABEL_FILE_EXT"]
    LABELS          = conf["LABELS"]

    show_help()

    wait_timer = 0

    img_File_List = [
        f for f in os.listdir(REP_images)
        if os.path.isfile(os.path.join(REP_images, f)) and f.lower().endswith(IMG_FILE_EXT)
    ]

    print(REP_images)
    print("   Nombre de fichier :", len(img_File_List))
    print()

    i = 0

    while True :

        img_File = img_File_List[i]

        label_File = img_File[:-len(IMG_FILE_EXT)] + LABEL_FILE_EXT


        print(img_File)
        print("   Label_File :", label_File )


        # Chargement de l'image
        image = cv2.imread( REP_images +"/"+ img_File )
        img_hauteur, img_largeur, _ = image.shape


        # lecture du fichier label
        if os.path.isfile(REP_labels +"/"+ label_File):
            f = open (REP_labels +"/"+ label_File, "r")


            # pour chaque label
            for line in f:
                print("   ", line, end="")
                
                data = line.split(" ")

                label_id = int(data[0])
                x_center = int(float(data[1]) * img_largeur)
                y_center = int(float(data[2]) * img_hauteur)
                x_box    = int(float(data[3]) * img_largeur /2)
                y_box    = int(float(data[4]) * img_hauteur /2)

           
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

                # Affichage le label

                texte = f"{LABELS[label_id]}"
                cv2.putText(image, texte, (x_center+12, y_center+2), font, 0.8, col_noir, 1, cv2.LINE_AA)
                cv2.putText(image, texte, (x_center+10, y_center), font, 0.8, col_blanc, 1, cv2.LINE_AA)

            f.close()
            print()

        else:
            print("   ERR : pas de fichier !!!")
            texte = f"ERR: pas de fichier Label !!!"
            cv2.putText(image, texte, (position_x+2, position_y+62), font, taille, col_noir, epaisseur, cv2.LINE_AA)
            cv2.putText(image, texte, (position_x, position_y+60), font, taille, col_rouge, epaisseur, cv2.LINE_AA)


        # Ajouter le texte sur l'image
        texte = f"Img index : {i} / {len(img_File_List)-1}"
        cv2.putText(image, texte, (position_x+2, position_y+2), font, taille, col_noir, epaisseur, cv2.LINE_AA)
        cv2.putText(image, texte, (position_x, position_y), font, taille, col_blanc, epaisseur, cv2.LINE_AA)

        texte = f"Img size : {img_largeur}x{img_hauteur}"
        cv2.putText(image, texte, (position_x+2, position_y+32), font, taille, col_noir, epaisseur, cv2.LINE_AA)
        cv2.putText(image, texte, (position_x, position_y+30), font, taille, col_blanc, epaisseur, cv2.LINE_AA)



        # Affichage de l'image
        cv2.imshow("Image", image)
        cv2.moveWindow("Image", int((screen_x - img_largeur)/2), int((screen_y - img_hauteur)/2))


        # ---------------------------------------
        # Gestion du clavier
        # Attendre l'appui d'une touche pendant x ms
        key = cv2.waitKey(wait_timer) & 0xFF

        if key == 27:                               exit()
        elif key == 32:                             wait_timer ^= 1
        elif key == 81 or key == ord("q") :         i -= 1
        elif key == 83 or key == ord("d") :         i += 1
        else:                                       i += 1


        if i >= len(img_File_List) :     
            i = len(img_File_List) - 1
            wait_timer = 0
        elif i < 0 :                    
            i = 0

        
    cv2.destroyAllWindows()

    print()
    print()

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
