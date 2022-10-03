void mycommand(
    char *datacfg,
    char *cfgfile,
    char *weightfile,
    float thresh,
    float hier_thresh,
    int dont_show,
    int ext_output,
    int save_labels,
    char *outfile,
    int letter_box)
{
    //
    // initialize.
    //
    list *options = read_data_cfg(datacfg);
    char *name_list = option_find_str(options, "names", "data/names.list");
    int names_size = 0;
    char **names = get_labels_custom(name_list, &names_size); //get_labels(name_list);
    image **alphabet = load_alphabet();
    network net = parse_network_cfg_custom(cfgfile, 1, 1); // set batch=1
    if (weightfile)
    {
        load_weights(&net, weightfile);
    }
    fuse_conv_batchnorm(net);
    calculate_binary_weights(net);
    if (net.layers[net.n - 1].classes != names_size)
    {
        printf(" Error: in the file %s number of names %d that isn't equal to classes=%d in the file %s \n",
               name_list, names_size, net.layers[net.n - 1].classes, cfgfile);
        if (net.layers[net.n - 1].classes > names_size)
            getchar();
    }
    srand(2222222);
    char buff[256] = {};
    char *input = buff;
    char *json_buf = NULL;
    int json_image_id = 0;
    FILE *json_file = NULL;
    if (outfile)
    {
        json_file = fopen(outfile, "wb");
        char *tmp = "[\n";
        fwrite(tmp, sizeof(char), strlen(tmp), json_file);
    }
    int j;
    float nms = .45; // 0.4F
    //
    // detect images.
    //
    int i = 0;
    while (1)
    {
        i++;
        if (i > 32)
        {
            break;
        }
        sprintf(input, "../test_images/%d.jpg", i);
        image im = load_image(input, 0, 0, net.c);
        image sized;
        if (letter_box)
            sized = letterbox_image(im, net.w, net.h);
        else
            sized = resize_image(im, net.w, net.h);
        layer l = net.layers[net.n - 1];
        float *X = sized.data;
        double time = get_time_point();
        network_predict(net, X);
        printf("%s: Predicted in %lf milli-seconds.\n", input, ((double)get_time_point() - time) / 1000);
        int nboxes = 0;
        detection *dets = get_network_boxes(&net, im.w, im.h, thresh, hier_thresh, 0, 1, &nboxes, letter_box);
        if (nms)
        {
            if (l.nms_kind == DEFAULT_NMS)
                do_nms_sort(dets, nboxes, l.classes, nms);
            else
                diounms_sort(dets, nboxes, l.classes, nms, l.nms_kind, l.beta_nms);
        }
        //
        // draw detections.
        //
        draw_detections_v3(im, dets, nboxes, thresh, names, alphabet, l.classes, ext_output);
        free_detections(dets, nboxes);
        free_image(im);
        free_image(sized);
        if (!dont_show)
        {
            wait_until_press_key_cv();
            destroy_all_windows_cv();
        }
    }
    if (outfile)
    {
        char *tmp = "\n]";
        fwrite(tmp, sizeof(char), strlen(tmp), json_file);
        fclose(json_file);
    }
    //
    // finalyze
    //
    free_ptrs((void **)names, net.layers[net.n - 1].classes);
    free_list_contents_kvp(options);
    free_list(options);
    const int nsize = 8;
    for (j = 0; j < nsize; ++j)
    {
        for (i = 32; i < 127; ++i)
        {
            free_image(alphabet[j][i]);
        }
        free(alphabet[j]);
    }
    free(alphabet);
    free_network(net);
}
