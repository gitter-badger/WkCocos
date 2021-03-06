package com.gameparkstudio.wkcocos.lib;

import android.os.Bundle;

import com.soomla.cocos2dx.common.ServiceManager;
import com.soomla.cocos2dx.store.StoreService;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

public class MainActivity extends Cocos2dxActivity {

    private final static String TAG = MainActivity.class.getSimpleName();

    private Cocos2dxWebViewHelper mWebViewHelper = null;

    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if(mWebViewHelper == null) {
            mWebViewHelper = new Cocos2dxWebViewHelper(mFrameLayout);
        }
    }

    @Override
    public Cocos2dxGLSurfaceView onCreateView() {

        Cocos2dxGLSurfaceView glSurfaceView = super.onCreateView();

        // initialize services
        final ServiceManager serviceManager = ServiceManager.getInstance();
        serviceManager.setActivity(this);
        serviceManager.setGlSurfaceView(glSurfaceView);
        serviceManager.registerService(StoreService.getInstance());

        return glSurfaceView;
    }


    @Override protected void onPause() {
        super.onPause();
        ServiceManager.getInstance().onPause();
    }

    @Override protected void onResume() {
        ServiceManager.getInstance().onResume();
        super.onResume();
    }
}
